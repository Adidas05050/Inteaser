#include "Player.h"
#include "iostream"
namespace
{
	const float PlayerBoxWidth = -56.f;
	const float PlayerBoxHeight = -32.f;
}
Player::Player(float x, float y, int health, int speed, Tile *level, sf::RenderWindow* window) {
	m_box.left = x + PlayerBoxWidth;
	m_box.top = y + PlayerBoxHeight;
	m_box.width = 20;
	m_box.height = 20;

	m_health = health;
	m_speed = speed;

	LoadImages();

	m_positionSprite = { x, y };
	m_playerSprite.setPosition(x, y);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	
	m_objectsSolid = level->GetAllObjects("wall");
	m_objectsSound = level->GetAllObjects("sound");

	// Костыль выставления скорости звука, надеюсь, временный
	stepSound[0].setPitch(1.5f);
	stepSound[1].setPitch(1.3f);

	m_healthBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Red);
	m_foodBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Yellow);

	m_healthBar->SetProgress(m_health / m_maxHealth);
	m_foodBar->SetProgress(m_food / m_maxFood);

	m_healthBar->SetPosition(sf::Vector2f(10, 10));
	m_foodBar->SetPosition(sf::Vector2f(10, 35));

	m_window = window;
}
//-------------------------------------------------------
void Player::LoadImages()
{
	// Up, Left, Right, Down
	// Idle, Walk, Attack, PickUp
	std::vector<sf::Texture> directionList;

	m_texture.loadFromFile("media/hero/idle_up.png");
	directionList.push_back(m_texture);

	m_texture.loadFromFile("media/hero/idle_side.png");
	directionList.push_back(m_texture);

	m_texture.loadFromFile("media/hero/idle_side.png");
	directionList.push_back(m_texture);

	m_texture.loadFromFile("media/hero/idle_down.png");
	directionList.push_back(m_texture);

	m_animationState[AnimState::Idle] = directionList;
	m_spritesInAnimation.push_back(5);

	//Walk
	directionList.clear();

	m_texture.loadFromFile("media/hero/walk_up.png");
	directionList.push_back(m_texture);

	m_texture.loadFromFile("media/hero/walk_side.png");
	directionList.push_back(m_texture);
									   
	m_texture.loadFromFile("media/hero/walk_side.png");
	directionList.push_back(m_texture);
									   
	m_texture.loadFromFile("media/hero/walk_down.png");
	directionList.push_back(m_texture);

	m_animationState[AnimState::Walk] = directionList;
	m_spritesInAnimation.push_back(6);

	//Attack
	directionList.clear();

	m_texture.loadFromFile("media/hero/attack_up.png");
	directionList.push_back(m_texture);

	m_texture.loadFromFile("media/hero/attack_side.png");
	directionList.push_back(m_texture);
									   
	m_texture.loadFromFile("media/hero/attack_side.png");
	directionList.push_back(m_texture);
									   
	m_texture.loadFromFile("media/hero/attack_down.png");
	directionList.push_back(m_texture);

	m_animationState[AnimState::Attack] = directionList;
	m_spritesInAnimation.push_back(3);

	//PickUp для всех направлений одинаков
	directionList.clear();

	m_texture.loadFromFile("media/hero/pick_up.png");
	directionList.push_back(m_texture);
	directionList.push_back(m_texture);
	directionList.push_back(m_texture);
	directionList.push_back(m_texture);

	m_animationState[AnimState::PickUp] = directionList;
	m_spritesInAnimation.push_back(5);

}
//-------------------------------------------------------
void Player::OnFrame(sf::View* view)
{
	if (m_frame > 64)
		m_frame = 0;

	if (m_frame % 4 == 0)
		m_currentSpriteTile++;

	Attack();
	PickUp();

	if (m_food < m_maxFood / 2 and m_health > m_maxHealth / 2)
		m_health -= m_decreaseFood;

	if (m_food < FLT_MIN)
		m_isWeak = true;

	if( m_food < m_maxFood)
		m_food += m_decreaseFood / 2;

	if (m_food >= m_maxFood)
		m_isWeak = false;

	m_healthBar->SetProgress(m_health/ m_maxHealth);
	m_foodBar->SetProgress(m_food/ m_maxFood);

	m_healthBar->Draw(view);
	m_foodBar->Draw(view);

	m_frame++;
}
//-------------------------------------------------------
void Player::Draw(float scaleX, float scaleY)
{
	const float playerWidth = scaleX * m_box.width / (float) m_box.width;
	const float playerHeight = scaleY * m_box.height / (float) m_box.height;


	if (m_currentSpriteTile >= m_spritesInAnimation[int(m_curAnimState)])
		ResetAnimation();

	// Выставление текстуры
	m_playerSprite.setTexture(m_animationState[m_curAnimState][static_cast<int>(m_direction)]);

	// Находим в текстуре анимации необходимый кусок. Поддерживает несколько строк в анимации
	const int widthTexture = int(m_animationState[m_curAnimState][static_cast<int>(m_direction)].getSize().x);

	m_currentColumn = m_currentSpriteTile % (widthTexture / PLAYER_WIDTH);

	if (PLAYER_WIDTH * m_currentSpriteTile - (widthTexture * m_currentRow) >= widthTexture)
		m_currentRow++;
	const bool isLeft = m_direction != Direction::Left;
	const auto& textureRect = sf::IntRect(	PLAYER_WIDTH * m_currentColumn + (isLeft ? PLAYER_WIDTH : 0), PLAYER_WIDTH * m_currentRow,
											isLeft ? -PLAYER_WIDTH : PLAYER_WIDTH, PLAYER_HEIGHT);
	m_playerSprite.setTextureRect(textureRect);

	// Выставление позиции
	m_positionSprite.x = m_box.left + PlayerBoxWidth;
	m_positionSprite.y = m_box.top + PlayerBoxHeight;
	m_playerSprite.setScale(playerWidth, playerHeight);
	m_playerSprite.setPosition(m_positionSprite);
	

	g_window->draw(m_playerSprite);

	// Collision box
	sf::RectangleShape recta;
	recta.setSize(sf::Vector2f(m_box.width, m_box.height));
	recta.setOrigin(sf::Vector2f(m_box.width / 2, m_box.height / 2));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(0, 0, 0, 0));
	recta.setOutlineColor(sf::Color(255, 0, 0));
	recta.setPosition(sf::Vector2f(m_box.left + m_box.width / 2, m_box.top + m_box.height / 2));

	g_window->draw(recta);
}
//-------------------------------------------------------
void Player::Move(Entity* entity)
{
	// При атаке стоим на месте и проверяем, долбанули ли мы кого-то
	if (m_attackState == ActionState::Running)
	{
		CollisionAttack(entity);
		return;
	}

	// Взаимодействие с предметами
	if (m_pickUpState == ActionState::Running)
		return;

	m_curSpeed = m_speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !m_isWeak)
	{
		m_curSpeed += 20;
		m_food -= m_decreaseFood;
	}

	m_curAnimState = AnimState::Idle;
	Direction direction = m_direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_box.top -= m_curSpeed;
		direction = Direction::Up;
		m_curAnimState = AnimState::Walk;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_box.top += m_curSpeed;
		direction = Direction::Down;
		m_curAnimState = AnimState::Walk;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_box.left += m_curSpeed;
		direction = Direction::Right;
		m_curAnimState = AnimState::Walk;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_box.left -= m_curSpeed;
		direction = Direction::Left;
		m_curAnimState = AnimState::Walk;
	}

	Collision(entity);

	if(direction != m_direction)
		ResetAnimation();

	m_direction = direction;

	// Звук шагов - off временно
	//if (m_isStay)
	//	stepSound[currentNumberSound].stop();
	//else if (stepSound[currentNumberSound].getStatus() != sf::SoundSource::Status::Playing)
	//{
	//	stepSound[0].setPlayingOffset(sf::Time(stepSound->getBuffer()->getDuration() / 2.f));
	//	stepSound[currentNumberSound].play(); //MUSIC
	//}

}
//-------------------------------------------------------
void Player::ResetAnimation()
{
	m_currentColumn = 0;
	m_currentRow = 0;
	m_currentSpriteTile = 0;

	if (m_attackState == ActionState::Running)
	{
		m_attackState = ActionState::Ended;
		m_curAnimState = AnimState::Idle;
	}

	if (m_pickUpState == ActionState::Running)
	{
		m_pickUpState = ActionState::Ended;
		m_curAnimState = AnimState::Idle;
	}
}
//-------------------------------------------------------
void Player::CollisionSound() {
	for(int i = 0; i < m_objectsSound.size(); i++) {
		if( GetRect().intersects(m_objectsSound[i].rect) and (previousNameSound != m_objectsSound[i].type)) {
			previousNameSound = m_objectsSound[i].type;
			for(it = tileMap.begin(); it != tileMap.end(); it++) {
				if(it->second == previousNameSound) {
					currentNumberSound = it->first;
					break;
				}
			}
			//std::cout << currentNumberSound << " " << previousNameSound;
		}
	}
}
//-------------------------------------------------------
void Player::CollisionAttack(Entity* entity)
{
	const sf::FloatRect enemyRect = entity->GetRect();
	m_collisionEntity = nullptr;
	const float widthAttack = m_direction == Direction::Left ? -75 : m_direction == Direction::Right ? 75 : 64;
	const float heightAttack = m_direction == Direction::Up ? -75 : m_direction == Direction::Down ? 75 : 64;

	sf::FloatRect rect(0, 0, widthAttack, heightAttack);
	float addWidth = 0.f;
	float addHeight = 0.f;
	switch (m_direction)
	{
	case Direction::Left:
		addWidth = m_playerSprite.getGlobalBounds().width / 2 + 20;
		addHeight = m_playerSprite.getGlobalBounds().height / 4;
		break;

	case Direction::Right:
		addWidth = m_playerSprite.getGlobalBounds().width / 2 - 20;
		addHeight = m_playerSprite.getGlobalBounds().height / 4;
		break;

	case Direction::Up:
		addWidth = m_playerSprite.getGlobalBounds().width / 4;
		addHeight = m_playerSprite.getGlobalBounds().height / 2 + 20;
		break;

	case Direction::Down:
		addWidth = m_playerSprite.getGlobalBounds().width / 4;
		addHeight = m_playerSprite.getGlobalBounds().height / 4 + 10;
		break;
	}

	rect.left +=  m_playerSprite.getGlobalBounds().left + addWidth;
	rect.top += m_playerSprite.getGlobalBounds().top + addHeight;
	if (rect.intersects(enemyRect))
		m_collisionEntity = entity;

	sf::RectangleShape recta;
	recta.setSize(sf::Vector2f(rect.width, rect.height));
	recta.setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(0, 0, 0, 0));
	recta.setOutlineColor(sf::Color(0, 255, 0));
	recta.setPosition(sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2));

	g_window->draw(recta);
}
//-------------------------------------------------------
void Player::Collision(Entity* entity)
{
	const sf::FloatRect enemyRect = entity->GetRect();

	Entity::Collision();
	
	m_box.top += m_speed;
	if(GetRect().intersects(enemyRect) )
	{
		m_box.top -= m_speed;
	}
	m_box.top -= m_speed;

	m_box.left += m_speed;
	if(GetRect().intersects(enemyRect) )
	{
		m_box.left -= m_speed;

	}
	m_box.left -= m_speed;

	m_box.left -= m_speed;
	if(GetRect().intersects(enemyRect) )
	{
		m_box.left += m_speed;

	}
	m_box.left += m_speed;

	m_box.top -= m_speed;
	if(GetRect().intersects(enemyRect) )
	{
		m_box.top += m_speed;
	}
	m_box.top += m_speed;

}
//-------------------------------------------------------
void Player::Attack()
{
	if (m_attackState == ActionState::Idle && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		ResetAnimation();
		m_attackState = ActionState::Running;
		m_curAnimState = AnimState::Attack;
	}
	else if (m_attackState == ActionState::Ended)
	{
		ResetAnimation();
		m_attackState = ActionState::Idle;
		m_curAnimState = AnimState::Idle;

		if(m_collisionEntity != nullptr)
			m_collisionEntity->SetDamage(10.f);
	}

}
//-------------------------------------------------------
void Player::PickUp()
{
	if (m_pickUpState == ActionState::Idle && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		ResetAnimation();
		m_pickUpState = ActionState::Running;
		m_curAnimState = AnimState::PickUp;
	}
	else if (m_pickUpState == ActionState::Ended)
	{
		ResetAnimation();
		m_pickUpState = ActionState::Idle;
		m_curAnimState = AnimState::Idle;
	}

}
//-------------------------------------------------------