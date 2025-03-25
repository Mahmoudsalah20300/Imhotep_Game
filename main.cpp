/**
 * main.cpp
 * 
 * This file serves as the entry point for a Game called Imhotep. 
 * Sets up the game network, validates player and round count, and runs the main game loop
 * where players compete. The program continues until the game reaches its designated end condition.
 * 
 * Group: 19
 * Author 12002760, 12347028, 12241141
 */

#include "network/Server.hpp"
#include "network/Exceptions.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <format>

/**
 * enum that represents the return values
 */
enum class ReturnValues
{
    SUCCESS = 0,
    WRONG_ARGUMENT_COUNT = 1,
    WRONG_ARGUMENT_VALUES = 2,
    NETWORK_ERROR = 3,
    RUNTIME_ERROR = 4
};

/**
 * Checks if the player count is in the correct range.
 * 
 * @param playerCount Number of players
 * @return true if player count is between 2 and 4, false otherwise
 */
bool isValidPlayerCount(int playerCount)
{
  return playerCount >= 2 && playerCount <= 4;
}

/**
 * Checks if the round count is in the correct range.
 * 
 * @param roundCount Number of rounds
 * @return true if round count is between 1 and 6, false otherwise
 */
bool isValidRoundCount(int roundCount)
{
  return roundCount >= 1 && roundCount <= 6;
}

/**
 * Parses a command-line argument as an integer.
 * 
 * @param arg The argument to parse
 * @param output Reference to store the parsed integer
 * @return true if parsing succeeds, false if invalid or out of range
 */
bool parseCommandLineArg(const std::string& arg, int& output)
{
  try
  {
    output = std::stoi(arg);
    return true;
  }
  catch (const std::invalid_argument&)
  {
    return false;
  }
  catch (const std::out_of_range&)
  {
    return false;
  }
}

/**
 * The main function for the Imhotep Game
 * 
 * Validates command-line arguments for player and round counts, then initializes 
 * the network and game. Runs the main game loop until the end condition is met.
 * Prints specific error messages and exits with appropriate codes on network or 
 * runtime errors.
 * 
 * @param argc Argument count
 * @param argv Command-line arguments
 * @return 0 for success, 1-4 for errors
 */
int main(int argc, char** argv)
{
  try
  {
    if (argc != 3)
    {
      std::cout << "ERROR: Usage ./imhotep_server PLAYER_COUNT ROUND_COUNT" << std::endl;
      return static_cast<int>(ReturnValues::WRONG_ARGUMENT_COUNT);
    }
    int player_count = 0;
    int round_count = 0;
    if (!parseCommandLineArg(argv[1], player_count) || !parseCommandLineArg(argv[2], round_count))
    {
      std::cout << "ERROR: Usage ./imhotep_server PLAYER_COUNT ROUND_COUNT" << std::endl;
      return static_cast<int>(ReturnValues::WRONG_ARGUMENT_VALUES);
    }

    if (!isValidPlayerCount(player_count) || !isValidRoundCount(round_count))
    {
      std::cout << "ERROR: Usage ./imhotep_server PLAYER_COUNT ROUND_COUNT" << std::endl;
      return static_cast<int>(ReturnValues::WRONG_ARGUMENT_VALUES);
    }
    
    net::Server network(player_count);
    Game game(player_count, round_count, network);
    game.startGame();
    
    while (!game.checkGameOver())
    {
      game.startRound();
      
      game.startTurn();

    }
  }
  catch (const net::NetworkException& e)
  {
    std::cerr << e.what() << std::endl;
    return static_cast<int>(ReturnValues::NETWORK_ERROR);
  }
  catch (const net::TimeoutException& e)
  {
    std::cerr << e.what() << std::endl;
    return static_cast<int>(ReturnValues::RUNTIME_ERROR);
  }
  return static_cast<int>(ReturnValues::SUCCESS);
}

// This is the comment to test

