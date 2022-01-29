//
// Created by toni on 25/01/22.
//

#ifndef AED_PROJ2_2021_CONSTANTS_H
#define AED_PROJ2_2021_CONSTANTS_H

#include <string>

/**
 * @brief Where the stops are stored.
 */
const std::string STOPS_FILE_PATH = "../dataset/lines-stops/stops.csv";
/**
 * @brief Where the lines are stored.
 */
const std::string LINE_FOLDER_PATH = "../dataset/lines/";

/**
 * @brief The line code for by foot edges.
 */
const std::string BY_FOOT_LINE = "A PÉ";
/**
 * @brief The stop code for the starting node.
 */
const std::string START_NODE = "START";
/**
 * @brief The stop name for the starting node.
 */
const std::string START_NODE_NAME = "Início";
/**
 * @brief The stop code for the ending node.
 */
const std::string END_NODE = "END";
/**
 * @brief The stop name for the ending node.
 */
const std::string END_NODE_NAME = "Fim";

// Terminal escape sequences
#ifdef NO_ANSI

const struct ClearScreen {
    friend std::ostream &operator<<(std::ostream &out, const ClearScreen &c) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        return out;
    }
} CLEAR_SCREEN;

const std::string RED_TEXT = "";
const std::string GREEN_TEXT = "";
const std::string CONCEAL_TEXT = "";
const std::string STRIKE_THROUGH = "";
const std::string DISABLE_CURSOR = "";
const std::string ENABLE_CURSOR = "";
const std::string RESET_FORMATTING = "";
const std::string STCP_BLUE = "";
const std::string STCP_CYAN = "";
#else
/**
 * @brief Clears the screen.
 *
 * @note May be implemented as an escape sequence or as a system call.
 */
const std::string CLEAR_SCREEN = "\33[2J\33[H";
/**
 * @brief Turns any text that follows red.
 *
 * @note May be disabled.
 */
const std::string RED_TEXT = "\33[31m";
/**
 * @brief Turns any text that follows green.
 *
 * @note May be disabled.
 */
const std::string GREEN_TEXT = "\33[32m";
/**
 * @brief Hides any text that follows.
 *
 * @note May be disabled.
 */
const std::string CONCEAL_TEXT = "\33[8m";
/**
 * @brief Crosses out any text that follows.
 *
 * @note May be disabled.
 */
const std::string STRIKE_THROUGH = "\33[9m";
/**
 * @brief Disables the terminal cursor.
 *
 * @note May be disabled.
 */
const std::string DISABLE_CURSOR = "\33[?25l";
/**
 * @brief Enables the terminal cursor.
 *
 * @note May be disabled.
 */
const std::string ENABLE_CURSOR = "\33[?25h";
/**
 * @brief Resets any text that follows back to normal.
 *
 * @note May be disabled.
 */
const std::string RESET_FORMATTING = "\33[0m";

/**
 * @brief Turns any text that follows blue.
 *
 * @note May be disabled.
 */
const std::string STCP_BLUE = "\33[38;2;0;92;185m";
/**
 * @brief Turns any text that follows cyan.
 *
 * @note May be disabled.
 */
const std::string STCP_CYAN = "\33[38;2;50;218;195m";
#endif // NO_ANSI

/**
 * @brief This program's name.
 */
const std::string PROGRAM_NAME =
    STCP_BLUE + "STC" + STCP_CYAN + "Plan" + RESET_FORMATTING;

#endif // AED_PROJ2_2021_CONSTANTS_H
