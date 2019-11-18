#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>


GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
    this->debug_rt = debug_rt;
    this->game_info = game_info;
    this->asteroid_observer = AsteroidsObserver(this);
    this->my_game_ai = new MyAIData();

    // customState().debug_on = false;
}

GameAI::~GameAI() {
    delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
    debug_rt->clear(sf::Color::Transparent);

    if (customState().debug_on) {
        if (not asteroidsObserver().asteroids().isEmpty()) {
            const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
            sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
            ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
            ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
            ast_rect.setOutlineColor(sf::Color::Yellow);
            ast_rect.setFillColor(sf::Color::Transparent);
            debug_rt->draw(ast_rect);
        }
    }
    
    // The angles 36000 and -36000 were chosen by testing several random angles
    // and these gave the highest score
    
    // If the degrees of the ship are 36000, then set the rotate to false, which
    // will allow the ship to fire anti-clockwise
    if(ship_state.millidegree_rotation == 36000){
        my_game_ai->rotate = true;
    // If the degrees of the ship are -36000, then set the rotate to false, which
    // will allow the ship to fire clockwise
    } else if(ship_state.millidegree_rotation == -36000){
        my_game_ai->rotate = false;
    }

    // Shoots in a certain direction depending on which degrees the ship is at 
    if(!(my_game_ai->rotate)){
        return SuggestedAction{SuggestedAction::YawingClockwise, SuggestedAction::FiringTry};
    } else if(my_game_ai->rotate){
        return SuggestedAction{SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry};
    }
}