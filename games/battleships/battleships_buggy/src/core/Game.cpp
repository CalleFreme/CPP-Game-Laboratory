#include "core/Game.h"

namespace bs {

    Game::Game(int width, int height)
        : m_width(width),
        m_height(height),
        m_players{ Player{"Player 1", width, height}, Player{"Player 2", width, height} }
    {
    }

    void Game::StartSetup()
    {
        m_state = GameState::Setup;
        m_current = 0;
        m_winner = -1;
        m_setupPlacedCount[0] = 0;
        m_setupPlacedCount[1] = 0;
    }

    PlaceResult Game::PlaceShipForCurrent(const Ship& ship)
    {
        if (m_state != GameState::Setup) return PlaceResult::Invalid;

        PlaceResult r = CurrentPlayerMut().own.PlaceShip(ship);
        if (r == PlaceResult::Ok)
            m_setupPlacedCount[m_current] += 1;

        return r;
    }

    void Game::NextPlayerDuringSetup()
    {
        // Hot-seat switch
        m_current = 1 - m_current;
    }

    void Game::FinishSetupIfReady()
    {
        // Intended by spec: only proceed when BOTH players placed ALL ships.
        // BUG: proceeds when *current player* finished, ignoring the other.
        if (m_setupPlacedCount[m_current] >= static_cast<int>(m_shipLengths.size()))
        {
            m_state = GameState::Playing;
            m_current = 0; // Player 1 starts
        }
    }

    ShotResult Game::ShootAtOpponent(Coord c)
    {
        if (m_state != GameState::Playing) return ShotResult::Invalid;

        ShotResult r = OtherPlayerMut().own.Shoot(c);

        // BUG: tracking board update is wrong: we mark Hit cells as Ship instead of Hit. - FIXED
        if (r == ShotResult::Miss)
            CurrentPlayerMut().tracking.SetCell(c, Cell::Miss);
        else if (r == ShotResult::Hit || r == ShotResult::Sunk)
            // It was obvious because you said the solution
            CurrentPlayerMut().tracking.SetCell(c, Cell::Hit); // BUG: should be Hit

        // BUG: win check uses current player's own board instead of opponent's board - FIXED
        // Change to OtherPlayer instead of CurrentPlayer
        if (OtherPlayer().own.AllShipsSunk())
        {
            m_state = GameState::GameOver;
            // We don't need to change because current player should be the winner if the other players ships have been sunk.
            m_winner = m_current; // BUG: declares shooter winner based on wrong check - FIXED
            return r;
        }
        AdvanceTurn();
        return r;
    }

    void Game::AdvanceTurn()
    {
        m_current = 1 - m_current;
    }

} // namespace bs