#include "pchOrange.h"
#include "KeyboardEvent.h"

#include "KeyboardCodes.h"


namespace Orange
{
    std::unordered_map<int, std::string> KeyboardEvent::s_KeyNames = {
        { ORANGE_KEY_UNKNOWN,           "Unknown"},
        { ORANGE_KEY_SPACE,             "Space"},
        { ORANGE_KEY_APOSTROPHE,        "'"},
        { ORANGE_KEY_COMMA,             ","},
        { ORANGE_KEY_MINUS,             "-"},
        { ORANGE_KEY_PERIOD,            "."},
        { ORANGE_KEY_SLASH,             "/"},
        { ORANGE_KEY_0,                 "0"},
        { ORANGE_KEY_1,                 "1"},
        { ORANGE_KEY_2,                 "2"},
        { ORANGE_KEY_3,                 "3"},
        { ORANGE_KEY_4,                 "4"},
        { ORANGE_KEY_5,                 "5"},
        { ORANGE_KEY_6,                 "6"},
        { ORANGE_KEY_7,                 "7"},
        { ORANGE_KEY_8,                 "8"},
        { ORANGE_KEY_9,                 "9"},
        { ORANGE_KEY_SEMICOLON,         ";"},
        { ORANGE_KEY_EQUAL,             "="},
        { ORANGE_KEY_A,                 "A"},
        { ORANGE_KEY_B,                 "B"},
        { ORANGE_KEY_C,                 "C"},
        { ORANGE_KEY_D,                 "D"},
        { ORANGE_KEY_E,                 "E"},
        { ORANGE_KEY_F,                 "F"},
        { ORANGE_KEY_G,                 "G"},
        { ORANGE_KEY_H,                 "H"},
        { ORANGE_KEY_I,                 "I"},
        { ORANGE_KEY_J,                 "J"},
        { ORANGE_KEY_K,                 "K"},
        { ORANGE_KEY_L,                 "L"},
        { ORANGE_KEY_M,                 "M"},
        { ORANGE_KEY_N,                 "N"},
        { ORANGE_KEY_O,                 "O"},
        { ORANGE_KEY_P,                 "P"},
        { ORANGE_KEY_Q,                 "Q"},
        { ORANGE_KEY_R,                 "R"},
        { ORANGE_KEY_S,                 "S"},
        { ORANGE_KEY_T,                 "T"},
        { ORANGE_KEY_U,                 "U"},
        { ORANGE_KEY_V,                 "V"},
        { ORANGE_KEY_W,                 "W"},
        { ORANGE_KEY_X,                 "X"},
        { ORANGE_KEY_Y,                 "Y"},
        { ORANGE_KEY_Z,                 "Z"},
        { ORANGE_KEY_LEFT_BRACKET,      "["},
        { ORANGE_KEY_BACKSLASH,         "\\"},
        { ORANGE_KEY_RIGHT_BRACKET,     "]"},
        { ORANGE_KEY_GRAVE_ACCENT,      "`"},
        { ORANGE_KEY_WORLD_1,           "Non-US #1"},
        { ORANGE_KEY_WORLD_2,           "Non-US #2"},
        { ORANGE_KEY_ESCAPE,            "Escape"},
        { ORANGE_KEY_ENTER,             "Enter"},
        { ORANGE_KEY_TAB,               "Tab"},
        { ORANGE_KEY_BACKSPACE,         "Backspace"},
        { ORANGE_KEY_INSERT,            "Insert"},
        { ORANGE_KEY_DELETE,            "Delete"},
        { ORANGE_KEY_RIGHT,             "Right Arrow"},
        { ORANGE_KEY_LEFT,              "Left Arrow"},
        { ORANGE_KEY_DOWN,              "Down Arrow"},
        { ORANGE_KEY_UP,                "Up Arrow"},
        { ORANGE_KEY_PAGE_UP,           "PgUp"},
        { ORANGE_KEY_PAGE_DOWN,         "PgDn"},
        { ORANGE_KEY_HOME,              "Home"},
        { ORANGE_KEY_END,               "End"},
        { ORANGE_KEY_CAPS_LOCK,         "CapsLock"},
        { ORANGE_KEY_SCROLL_LOCK,       "ScrollLock"},
        { ORANGE_KEY_NUM_LOCK,          "NumLock"},
        { ORANGE_KEY_PRINT_SCREEN,      "PrtSc"},
        { ORANGE_KEY_PAUSE,             "Pause"},
        { ORANGE_KEY_F1,                "F1"},
        { ORANGE_KEY_F2,                "F2"},
        { ORANGE_KEY_F3,                "F3"},
        { ORANGE_KEY_F4,                "F4"},
        { ORANGE_KEY_F5,                "F5"},
        { ORANGE_KEY_F6,                "F6"},
        { ORANGE_KEY_F7,                "F7"},
        { ORANGE_KEY_F8,                "F8"},
        { ORANGE_KEY_F9,                "F9"},
        { ORANGE_KEY_F10,               "F10"},
        { ORANGE_KEY_F11,               "F11"},
        { ORANGE_KEY_F12,               "F12"},
        { ORANGE_KEY_F13,               "F13"},
        { ORANGE_KEY_F14,               "F14"},
        { ORANGE_KEY_F15,               "F15"},
        { ORANGE_KEY_F16,               "F16"},
        { ORANGE_KEY_F17,               "F17"},
        { ORANGE_KEY_F18,               "F18"},
        { ORANGE_KEY_F19,               "F19"},
        { ORANGE_KEY_F20,               "F20"},
        { ORANGE_KEY_F21,               "F21"},
        { ORANGE_KEY_F22,               "F22"},
        { ORANGE_KEY_F23,               "F23"},
        { ORANGE_KEY_F24,               "F24"},
        { ORANGE_KEY_F25,               "F25"},
        { ORANGE_KEY_NUMPAD_0,          "Numpad 0"},
        { ORANGE_KEY_NUMPAD_1,          "Numpad 1"},
        { ORANGE_KEY_NUMPAD_2,          "Numpad 2"},
        { ORANGE_KEY_NUMPAD_3,          "Numpad 3"},
        { ORANGE_KEY_NUMPAD_4,          "Numpad 4"},
        { ORANGE_KEY_NUMPAD_5,          "Numpad 5"},
        { ORANGE_KEY_NUMPAD_6,          "Numpad 6"},
        { ORANGE_KEY_NUMPAD_7,          "Numpad 7"},
        { ORANGE_KEY_NUMPAD_8,          "Numpad 8"},
        { ORANGE_KEY_NUMPAD_9,          "Numpad 9"},
        { ORANGE_KEY_NUMPAD_DECIMAL,    "Numpad ." },
        { ORANGE_KEY_NUMPAD_DIVIDE,     "Numpad /" },
        { ORANGE_KEY_NUMPAD_MULTIPLY,   "Numpad *" },
        { ORANGE_KEY_NUMPAD_SUBTRACT,   "Numpad -" },
        { ORANGE_KEY_NUMPAD_ADD,        "Numpad +" },
        { ORANGE_KEY_NUMPAD_ENTER,      "Numpad Enter" },
        { ORANGE_KEY_NUMPAD_EQUAL,      "Numpad =" },
        { ORANGE_KEY_LEFT_SHIFT,        "Left Shift" },
        { ORANGE_KEY_RIGHT_SHIFT,       "Right Shift" },
        { ORANGE_KEY_LEFT_CONTROL,      "Left Control" },
        { ORANGE_KEY_RIGHT_CONTROL,     "Right Control" },
        { ORANGE_KEY_LEFT_ALT,          "Left Alt" },
        { ORANGE_KEY_RIGHT_ALT,         "Right Alt" },
        { ORANGE_KEY_LEFT_SUPER,        "Left Super" },
        { ORANGE_KEY_RIGHT_SUPER,       "Right Super" },
        { ORANGE_KEY_MENU,              "Menu"},
    };
    
    std::string KeyboardEvent::ToString() const
    {
        std::stringstream ss;
        ss << this->GetName() << ": ";
        if (s_KeyNames.find(m_Key) == s_KeyNames.end())
            ss << m_Key;
        else ss << s_KeyNames[m_Key];
        return ss.str();
    }

    std::string CharEvent::ToString() const
    {
        std::stringstream ss;
        ss << this->GetName() << ": " << (char)m_Char;
        return ss.str();
    }
}


