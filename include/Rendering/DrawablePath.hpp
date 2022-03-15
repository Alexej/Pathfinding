#ifndef D5E0926D_6CA1_4674_9DF6_205CB3BD64C3
#define D5E0926D_6CA1_4674_9DF6_205CB3BD64C3

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>

namespace Pathfinding::Datastructures {struct Node;}
namespace Pathfinding::Core {struct ApplicationState;}


namespace Pathfinding::Rendering
{
    class DrawablePath final : public sf::Drawable
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PCApplicationState = Pathfinding::Core::ApplicationState;
        public:
            void init(const PCApplicationState * appStateSPtr);

            void prepare(const std::vector<PDNode *> &path, 
                        sf::Vector2f pointPositionOffset, 
                        sf::Color color);

            void resize(float nodePointRadius, 
                    sf::Vector2f straughtLineSize, 
                    sf::Vector2f diagonalLineSize, 
                    sf::Vector2f origin);

        private:
            void setColor(sf::Color color);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void drawPathPoints();

            void drawPathLines();

            void createPathPoints(const std::vector<PDNode *> &path, 
                                 sf::Vector2f pointPositionOffset);

            void createPathLines(const std::vector<PDNode *> &path, 
                                 sf::Vector2f pointPositionOffset);

        private:
            sf::CircleShape nodePoint;
            sf::RectangleShape diagonalLine;
            sf::RectangleShape straightLine;
            bool drawPathPointsFlag = false;
            bool drawPathLinesFlag = false;
            std::vector<sf::RectangleShape> lines;
            std::vector<sf::CircleShape> points;
            const PCApplicationState * appStatePtr;
    };
}


#endif /* D5E0926D_6CA1_4674_9DF6_205CB3BD64C3 */
