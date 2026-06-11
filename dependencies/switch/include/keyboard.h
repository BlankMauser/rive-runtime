#include <stdint.h>

static char KEY_TABLE[] =
    "\0\0\0\0abcdefghijkl"
    "mnopqrstuvwxyz12"
    "34567890\n\033\b\t -=["
    "]\\~;\'`,./\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0/*-+\n1234567"
    "890.\\\0\0=\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0,\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

static char SHIFTED_KEY_TABLE[] =
    "\0\0\0\0ABCDEFGHIJKL"
    "MNOPQRSTUVWXYZ!@"
    "#$%^&*()\n\033\b\t _+{"
    "}|~:\"~<>?\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0/*-+\n1234567"
    "890.\\\0\0=\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0,\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

enum KeyboardKey {
    A = 0x04,               
    B = 0x05,               
    C = 0x06,               
    D = 0x07,               
    E = 0x08,               
    F = 0x09,               
    G = 0x0A,               
    H = 0x0B,               
    I = 0x0C,               
    J = 0x0D,               
    K = 0x0E,               
    L = 0x0F,               
    M = 0x10,               
    N = 0x11,               
    O = 0x12,               
    P = 0x13,               
    Q = 0x14,               
    R = 0x15,               
    S = 0x16,               
    T = 0x17,               
    U = 0x18,               
    V = 0x19,               
    W = 0x1A,               
    X = 0x1B,               
    Y = 0x1C,               
    Z = 0x1D,               
    D1 = 0x1E,              
    D2 = 0x1F,              
    D3 = 0x20,              
    D4 = 0x21,              
    D5 = 0x22,              
    D6 = 0x23,              
    D7 = 0x24,              
    D8 = 0x25,              
    D9 = 0x26,              
    D0 = 0x27,              
    Return = 0x28,          
    Escape = 0x29,          
    Backspace = 0x2A,       
    Tab = 0x2B,             
    Space = 0x2C,           
    Minus = 0x2D,           
    Plus = 0x2E,            
    OpenBracket = 0x2F,     
    CloseBracket = 0x30,    
    Pipe = 0x31,            
    Tilde = 0x32,           
    Semicolon = 0x33,       
    Quote = 0x34,           
    Backquote = 0x35,       
    Comma = 0x36,           
    Period = 0x37,          
    Slash = 0x38,           
    CapsLock = 0x39,        
    F1 = 0x3A,              
    F2 = 0x3B,              
    F3 = 0x3C,              
    F4 = 0x3D,              
    F5 = 0x3E,              
    F6 = 0x3F,              
    F7 = 0x40,              
    F8 = 0x41,              
    F9 = 0x42,              
    F10 = 0x43,             
    F11 = 0x44,             
    F12 = 0x45,             
    PrintScreen = 0x46,     
    ScrollLock = 0x47,      
    Pause = 0x48,           
    Insert = 0x49,          
    Home = 0x4A,            
    PageUp = 0x4B,          
    Delete = 0x4C,          
    End = 0x4D,             
    PageDown = 0x4E,        
    RightArrow = 0x4F,      
    LeftArrow = 0x50,       
    DownArrow = 0x51,       
    UpArrow = 0x52,         
    NumLock = 0x53,         
    NumPadDivide = 0x54,    
    NumPadMultiply = 0x55,  
    NumPadSubtract = 0x56,  
    NumPadAdd = 0x57,       
    NumPadEnter = 0x58,     
    NumPad1 = 0x59,         
    NumPad2 = 0x5A,         
    NumPad3 = 0x5B,         
    NumPad4 = 0x5C,         
    NumPad5 = 0x5D,         
    NumPad6 = 0x5E,         
    NumPad7 = 0x5F,         
    NumPad8 = 0x60,         
    NumPad9 = 0x61,         
    NumPad0 = 0x62,         
    NumPadDot = 0x63,       
    Backslash = 0x64,       
    Application = 0x65,     
    Power = 0x66,           
    NumPadEquals = 0x67,    
    F13 = 0x68,             
    F14 = 0x69,             
    F15 = 0x6A,             
    F16 = 0x6B,             
    F17 = 0x6C,             
    F18 = 0x6D,             
    F19 = 0x6E,             
    F20 = 0x6F,             
    F21 = 0x70,             
    F22 = 0x71,             
    F23 = 0x72,             
    F24 = 0x73,             
    NumPadComma = 0x85,     
    Ro = 0x87,              
    KatakanaHiragana = 0x88,
    Yen = 0x89,             
    Henkan = 0x8A,          
    Muhenkan = 0x8B,        
    NumPadCommaPc98 = 0x8C, 
    HangulEnglish = 0x90,   
    Hanja = 0x91,           
    Katakana = 0x92,        
    Hiragana = 0x93,        
    ZenkakuHankaku = 0x94,  
    LeftControl = 0xE0,     
    LeftShift = 0xE1,       
    LeftAlt = 0xE2,         
    LeftGui = 0xE3,         
    RightControl = 0xE4,    
    RightShift = 0xE5,      
    RightAlt = 0xE6,        
    RightGui = 0xE7,        
};

enum KeyboardModifiers {
    Control = 0,
    Shift = 1,
    MLeftAlt = 2,
    MRightAlt = 3,
    Gui = 4,
    MCapsLock = 8,
    MScrollLock = 9,
    MNumLock = 10,
    MKatakana = 11,
    MHiragana = 12
};

namespace nn::hid {
    struct KeyboardState {
        int64_t sampling_number;
        uint32_t modifiers;
        uint32_t padding;
        uint64_t key_state[4];

        bool is_key(KeyboardKey k) const {
            int idx = ((int)k / 0x40);
            uint64_t bit = (uint64_t)1 << ((int)k % 0x40);
            return (this->key_state[idx] & bit) != 0;
        }

        bool is_mod(KeyboardModifiers m) const {
            uint32_t bit = 1 << (int)m;
            return (this->modifiers & bit) != 0;
        }
    };
    void InitializeKeyboard();
    void GetKeyboardState(KeyboardState* out_state);
    int GetKeyboardStates(KeyboardState* out_states, int count);
}


class UserKeyboard {
    public:
        union EventObject {
            KeyboardKey key;
            KeyboardModifiers mod;
        };

        enum class EventType {
            KeyPress,
            KeyRelease,
            ModPress,
            ModRelease
        };

        typedef void (*OnKeyEvent)(const nn::hid::KeyboardState& state, EventType type, EventObject obj);

    private:
        OnKeyEvent on_event;
        nn::hid::KeyboardState* state;
        nn::hid::KeyboardState* prev_state;

    public:
        UserKeyboard() {
            this->on_event = nullptr;
            this->state = new nn::hid::KeyboardState;
            this->prev_state = new nn::hid::KeyboardState;
            nn::hid::InitializeKeyboard();
            nn::hid::GetKeyboardState(prev_state);
            nn::hid::GetKeyboardState(state);
        }

        UserKeyboard(OnKeyEvent event_fn) : UserKeyboard() {
            this->on_event = event_fn;
        }

        UserKeyboard(const UserKeyboard&) = delete;
        UserKeyboard(UserKeyboard&&)      = delete;

        void Update() {
            std::swap(this->prev_state, this->state);
            nn::hid::GetKeyboardState(this->state);
            if (this->on_event) {
                for (int i = 0; i < 0x100; i++) {
                    if (this->IsKeyDown((KeyboardKey)i))
                        this->on_event(*this->state, EventType::KeyPress, EventObject { .key = (KeyboardKey)i });
                    else if (this->IsKeyUp((KeyboardKey)i))
                        this->on_event(*this->state, EventType::KeyRelease, EventObject { .key = (KeyboardKey)i });
                }
                for (int i = 0; i < 0x20; i++) {
                    if (this->IsModDown((KeyboardModifiers)i))
                        this->on_event(*this->state, EventType::ModPress, EventObject { .mod = (KeyboardModifiers)i });
                    else if (this->IsModUp((KeyboardModifiers)i))
                        this->on_event(*this->state, EventType::ModRelease, EventObject { .mod = (KeyboardModifiers)i });
                }
            }
        }
        bool IsKeyDown(KeyboardKey key) const {
            return this->state->is_key(key) && !this->prev_state->is_key(key);
        }
        bool IsKeyUp(KeyboardKey key) const {
            return !this->state->is_key(key) && this->prev_state->is_key(key);
        }
        bool IsKeyHeld(KeyboardKey key) const {
            return this->state->is_key(key) && this->prev_state->is_key(key);
        }
        bool IsKey(KeyboardKey key) const {
            return this->state->is_key(key);
        }


        bool IsModDown(KeyboardModifiers mod) const {
            return this->state->is_mod(mod) && !this->prev_state->is_mod(mod);
        }
        bool IsModUp(KeyboardModifiers mod) const {
            return !this->state->is_mod(mod) && this->prev_state->is_mod(mod);
        }
        bool IsKeyHeld(KeyboardModifiers mod) const {
            return !this->state->is_mod(mod) && this->prev_state->is_mod(mod);
        }
        bool IsMod(KeyboardModifiers mod) const {
            return this->state->is_mod(mod);
        }

        const nn::hid::KeyboardState& CurrentState() const {
            return *this->state;
        }

        void SetEventCallback(OnKeyEvent event_fn) {
            this->on_event = event_fn;
        }
};