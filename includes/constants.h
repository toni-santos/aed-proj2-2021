//
// Created by toni on 25/01/22.
//

#ifndef AED_PROJ2_2021_CONSTANTS_H
#define AED_PROJ2_2021_CONSTANTS_H

#include <string>

const std::string STOPS_FILE_PATH = "../dataset/lines-stops/stops.csv";
const std::string LINES_FILE_PATH = "../dataset/lines-stops/lines.csv";
const std::string LINE_FOLDER_PATH = "../dataset/lines/";


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
#endif // NO_ANSI

#endif // AED_PROJ2_2021_CONSTANTS_H
