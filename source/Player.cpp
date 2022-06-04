#include "Player.h"
#include "iostream"

Player::Player(int x, int y, int health, int speed, Tile *level, sf::RenderWindow* window) {
	m_box.left = x;
	m_box.top = y;
	m_box.width = 64;
	m_box.height = 64;

	m_health = health;
	m_speed = speed;

	LoadImages();

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
	m_playerSprite.setScale(playerWidth, playerHeight);
	m_playerSprite.setPosition(m_box.left - m_box.width / 2, m_box.top - m_box.height / 2);


	g_window->draw(m_playerSprite);
}
//-------------------------------------------------------
void Player::Move(sf::FloatRect enemyRect)
{
	// При атаке стоим на месте
	if (m_attackState == ActionState::Running)
		return;

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

	Сollision(enemyRect);

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
void Player::Сollision(sf::FloatRect enemyRect) 
{
	for(int i = 0; i < m_objectsSolid.size(); i++)
	{

		m_box.top += m_curSpeed;
		if( GetRect().intersects(m_objectsSolid[i].rect))
		{
			m_box.top -= m_curSpeed;
		}
		m_box.top -= m_curSpeed;

		m_box.top -= m_curSpeed;
		if (GetRect().intersects(m_objectsSolid[i].rect))
		{
			m_box.top += m_curSpeed;
		}
		m_box.top += m_curSpeed;

		m_box.left += m_curSpeed;
		if(GetRect().intersects(m_objectsSolid[i].rect) )
		{
			m_box.left -= m_curSpeed;
		}
		m_box.left -= m_curSpeed;

		m_box.left -= m_curSpeed;
		if(GetRect().intersects(m_objectsSolid[i].rect) )
		{
			m_box.left += m_curSpeed;
		}
		m_box.left += m_curSpeed;
		
	}
	
	for(int i = 0; i < 1; i++) 
	{
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
// ProgressBar
//-------------------------------------------------------
Player::ProgressBar::ProgressBar(sf::Vector2f size, sf::Color color)
{
	m_background.setSize(size);
	m_background.setFillColor(sf::Color::Black);
	m_foreground.setSize(size);
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Player::ProgressBar::SetProgress(float progress)
{
	m_foreground.setScale(progress, 1.f);
}
//-------------------------------------------------------
void Player::ProgressBar::SetColor(sf::Color color)
{
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Player::ProgressBar::SetPosition(sf::Vector2f position)
{
	m_position = position;
}
//-------------------------------------------------------
void Player::ProgressBar::Draw(sf::View* view)
{
	const auto& coordBegin = view->getCenter() - view->getSize() / 2.f;
	sf::Vector2f positionOnView = sf::Vector2f(m_position.x + coordBegin.x, m_position.y + coordBegin.y);
	m_background.setPosition(positionOnView);
	m_foreground.setPosition(positionOnView);
	g_window->draw(m_background);
	g_window->draw(m_foreground);
}
//-------------------------------------------------------