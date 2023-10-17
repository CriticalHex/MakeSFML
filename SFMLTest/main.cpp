#include<iostream>
#include<math.h>
#include<SFML\Graphics.hpp>
#include<vector>
#include<random>
#include<ctime>

using namespace std;


class Curve
{
public:
	Curve(int points) {
		res = .01;

		curve.setPrimitiveType(sf::PrimitiveType::LineStrip);

		for (int i = 0; i < points; i++) {
			anchors.push_back(new Anchor(randPos()));
		}

		calculate(anchors, curve);

	}

	~Curve() {}

	void process(sf::RenderWindow& window) {

		for (auto anchor : anchors) {
			anchor->update();
		}

		curve.clear();

		calculate(anchors, curve);

		draw(window);

	}

	void setResolution(double resolution) { res = resolution; }

	void setColor(sf::Color color) { c = color; set = true; }

private:
	sf::VertexArray curve;

	double res;

	sf::Color c;
	bool set = false;

	void draw(sf::RenderWindow& window) {
		window.draw(curve);
	}

	class Anchor
	{
	public:
		Anchor(sf::Vector2f position) {
			pos = position;
			d.x = rand() % 3 + 1;
			d.y = rand() % 3 + 1;
		}

		~Anchor() {}

		void update() { collide(); pos += d; }

		sf::Vector2f getPos() { return pos; }

		void setPos(sf::Vector2f position) { pos = position; }

	private:
		sf::Vector2f pos;
		sf::Vector2f d;

		void collide() {
			if (pos.x >= 1920 or pos.x <= 0) {
				d.x *= -1;
			}
			if (pos.y >= 1080 or pos.y <= 0) {
				d.y *= -1;
			}
		}

	};

	sf::Vector2f lerp(sf::Vector2f p1, sf::Vector2f p2, double t) {
		return sf::Vector2f(p1.x + (p2.x - p1.x) * t, p1.y + (p2.y - p1.y) * t);
	}

	sf::Vector2f bezier(vector<Anchor*> anchors, double t) {
		if (anchors.size() == 2) {
			return lerp(anchors[0]->getPos(), anchors[1]->getPos(), t);
		}
		vector<Anchor*> c1 = anchors;
		c1.pop_back();

		vector<Anchor*> c2 = anchors;
		c2.erase(c2.begin());

		sf::Vector2f p1 = bezier(c1, t);
		sf::Vector2f p2 = bezier(c2, t);

		return lerp(p1, p2, t);
	}

	void calculate(vector<Anchor*> anchors, sf::VertexArray& curve) {
		for (double t = 0; t <= 1; t += res) {
			if (set)
				curve.append(sf::Vertex(bezier(anchors, t), c));
			else
				curve.append(sf::Vertex(bezier(anchors, t), sf::Color(t * 360, 255, 255)));
		}
	}

	sf::Vector2f randPos() {
		return sf::Vector2f(rand() % 1919 + 1, rand() % 1079 + 1);
	}

	vector<Anchor*> anchors;

};




int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Bezier Curves", sf::Style::Fullscreen);
	window.setFramerateLimit(144);
	sf::Vector2f center(window.getSize().x / 2, window.getSize().y / 2);
	sf::Color bgColor = sf::Color(6, 8, 12);
	sf::Event event;
	
	Curve c1 = Curve(4); // iffy past 10 points.
	c1.setColor(sf::Color::Red);
	Curve c2 = Curve(4);
	c2.setColor(sf::Color::Green);
	Curve c3 = Curve(4);
	c3.setColor(sf::Color::Blue);


	while (window.isOpen()) {
		while (window.pollEvent(event))
		{
			// Close window: exit-----------------
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				window.close();
			}

		}

		window.clear(bgColor);

		c1.process(window);
		c2.process(window);
		c3.process(window);

		window.display();
	}

}