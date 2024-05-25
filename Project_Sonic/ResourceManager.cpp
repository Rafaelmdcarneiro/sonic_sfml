#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	// loading resources

	sf::Texture a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u,
		play_button, exit_button, resume_button, start_menu, winning_menu, game_over_menu,
		background, ring, diamond;

	sf::SoundBuffer open_menu_sound, //SoundBuffer
		game_over_sound,
		winning_sound,
		start_game_sound,
		soundtrack_sound,
		level_success_sound,
		eat_ring_sound,
		strike_sound,
		button_touched;

	sf::SoundBuffer sonic_death, bomb;
	std::string exeption_msg = "error in loading file\n";

	if (!a.loadFromFile(PATH_GRASS))
		throw std::runtime_error(exeption_msg);
	if (!b.loadFromFile(PATH_WALL))
		throw std::runtime_error(exeption_msg);
	if (!d.loadFromFile(PATH_SONIC_ANIMATION1))
		throw std::runtime_error(exeption_msg);
	if (!e.loadFromFile(PATH_SONIC_ANIMATION2))
		throw std::runtime_error(exeption_msg);
	if (!f.loadFromFile(PATH_SONIC_ANIMATION3))
		throw std::runtime_error(exeption_msg);
	if (!g.loadFromFile(PATH_SONIC_ANIMATION4))
		throw std::runtime_error(exeption_msg);
	if (!h.loadFromFile(PATH_SONIC_JUMP1))
		throw std::runtime_error(exeption_msg);
	if (!i.loadFromFile(PATH_SONIC_JUMP2))
		throw std::runtime_error(exeption_msg);
	if (!j.loadFromFile(PATH_SONIC_JUMP3))
		throw std::runtime_error(exeption_msg);

	if (!k.loadFromFile(PATH_BAETLE_ANIMATION1))
		throw std::runtime_error(exeption_msg);
	if (!l.loadFromFile(PATH_BAETLE_ANIMATION2))
		throw std::runtime_error(exeption_msg);
	if (!m.loadFromFile(PATH_BAETLE_ANIMATION3))
		throw std::runtime_error(exeption_msg);
	if (!n.loadFromFile(PATH_CRAB_ANIMATION1))
		throw std::runtime_error(exeption_msg);
	if (!o.loadFromFile(PATH_CRAB_ANIMATION2))
		throw std::runtime_error(exeption_msg);
	if (!p.loadFromFile(PATH_CRAB_ANIMATION3))
		throw std::runtime_error(exeption_msg);
	if (!q.loadFromFile(PATH_CRAB_ANIMATION4))
		throw std::runtime_error(exeption_msg);
	if (!r.loadFromFile(PATH_EXPLOSION))
		throw std::runtime_error(exeption_msg);
	if (!s.loadFromFile(PATH_BOSS_ANIMATION1))
		throw std::runtime_error(exeption_msg);
	if (!t.loadFromFile(PATH_BOSS_ANIMATION2))
		throw std::runtime_error(exeption_msg);
	if (!u.loadFromFile(PATH_BOSS_ANIMATION3))
		throw std::runtime_error(exeption_msg);


	if (!play_button.loadFromFile(PATH_PLAY_BUTTON))
		throw std::runtime_error(exeption_msg);
	if (!exit_button.loadFromFile(PATH_EXIT_BUTTON))
		throw std::runtime_error(exeption_msg);
	if (!resume_button.loadFromFile(PATH_RESUME))
		throw std::runtime_error(exeption_msg);
	if (!start_menu.loadFromFile(PATH_START_MENU))
		throw std::runtime_error(exeption_msg);
	if (!winning_menu.loadFromFile(PATH_WIN_MENU))
		throw std::runtime_error(exeption_msg);
	if (!game_over_menu.loadFromFile(PATH_GAME_OVER))
		throw std::runtime_error(exeption_msg);
	if (!background.loadFromFile(PATH_BACKGROUND))
		throw std::runtime_error(exeption_msg);
	if (!ring.loadFromFile(PATH_RING))
		throw std::runtime_error(exeption_msg);
	if (!diamond.loadFromFile(PATH_DIAMOND))
		throw std::runtime_error(exeption_msg);
	if (!m_font.loadFromFile(PATH_FONT))
		throw std::runtime_error(exeption_msg);


	if (!button_touched.loadFromFile(PATH_BOTTUN_TOUCHED_SOUND))
		throw std::runtime_error(exeption_msg);


	if (!soundtrack_sound.loadFromFile(PATH_SOUND_TRACK))
		throw std::runtime_error(exeption_msg);

	if (!eat_ring_sound.loadFromFile(PATH_EAT_SOUND))
		throw std::runtime_error(exeption_msg);

	if (!sonic_death.loadFromFile(PATH_SONIC_DEATH_SOUND))
		throw std::runtime_error(exeption_msg);
	if (!bomb.loadFromFile(PATH_SONIC_KILL_SOUND))
		throw std::runtime_error(exeption_msg);



	m_pictures.insert(std::pair<std::string, sf::Texture>(GRASS, a));
	m_pictures.insert(std::pair<std::string, sf::Texture>(WALL, b));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_ANIMATION1, d));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_ANIMATION2, e));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_ANIMATION3, f));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_ANIMATION4, g));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_JUMP1, h));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_JUMP2, i));
	m_pictures.insert(std::pair<std::string, sf::Texture>(SONIC_JUMP3, j));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BAETLE_ANIMATION1, k));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BAETLE_ANIMATION2, l));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BAETLE_ANIMATION3, m));
	m_pictures.insert(std::pair<std::string, sf::Texture>(CRAB_ANIMATION1, n));
	m_pictures.insert(std::pair<std::string, sf::Texture>(CRAB_ANIMATION2, o));
	m_pictures.insert(std::pair<std::string, sf::Texture>(CRAB_ANIMATION3, p));
	m_pictures.insert(std::pair<std::string, sf::Texture>(CRAB_ANIMATION4, q));
	m_pictures.insert(std::pair<std::string, sf::Texture>(EXPLOSION, r));

	m_pictures.insert(std::pair<std::string, sf::Texture>(PLAY_BUTTON, play_button));
	m_pictures.insert(std::pair<std::string, sf::Texture>(EXIT_BUTTON, exit_button));
	m_pictures.insert(std::pair<std::string, sf::Texture>(START_MENU, start_menu));
	m_pictures.insert(std::pair<std::string, sf::Texture>(RESUME, resume_button));
	m_pictures.insert(std::pair<std::string, sf::Texture>(WIN_MENU, winning_menu));
	m_pictures.insert(std::pair<std::string, sf::Texture>(GAME_OVER, game_over_menu));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BACKGROUND, background));
	m_pictures.insert(std::pair<std::string, sf::Texture>(RING, ring));
	m_pictures.insert(std::pair<std::string, sf::Texture>(DIAMOND, diamond));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BOSS_ANIMATION1, s));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BOSS_ANIMATION2, t));
	m_pictures.insert(std::pair<std::string, sf::Texture>(BOSS_ANIMATION3, u));



	m_sounds.insert(std::pair<std::string, sf::SoundBuffer>(BOTTUN_TOUCHED_SOUND, button_touched));
	m_sounds.insert(std::pair<std::string, sf::SoundBuffer>(SOUND_TRACK, soundtrack_sound));
	m_sounds.insert(std::pair<std::string, sf::SoundBuffer>(EAT_SOUND, eat_ring_sound));
	m_sounds.insert(std::pair<std::string, sf::SoundBuffer>(SONIC_KILL_SOUND, bomb));
	m_sounds.insert(std::pair<std::string, sf::SoundBuffer>(SONIC_DEATH_SOUND, sonic_death));



}

// return the object
ResourceManager & ResourceManager::instance()
{
	static ResourceManager m_instance;
	return m_instance;

}

// return the specifc soundbuffer
const sf::SoundBuffer & ResourceManager::GetAudio(const std::string & name)
{
	auto search = m_sounds.find(name);
	if (search != m_sounds.end())
		return search->second;
}

// return the specifc texture
const sf::Texture & ResourceManager::GetTexture(const std::string & name)
{
	auto search = m_pictures.find(name);
	if (search != m_pictures.end()) 
		return search->second;

}

// get font
const sf::Font & ResourceManager::GetFont() const
{
	return m_font;
}

ResourceManager::~ResourceManager()
{
}
