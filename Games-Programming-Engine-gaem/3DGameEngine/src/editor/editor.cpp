#include "editor\editor.h"

void Editor::startup(HINSTANCE hInstance, Engine* engine, EditorCamera* editorCam)
{
	_hInstance = hInstance;
	_menuBar.initialize(hInstance, _goMenu, engine);
	_goMenu.initialize(engine->getObjectManager(), engine->getSceneManager(), editorCam);
	initConsole();

	_processTwEvents = false; // must be false at start as it crashes for some reason (something to do with premature handling of mouse move event)
}

void Editor::update()
{
	_goMenu.update();
	_processTwEvents = !_menuBar.gamePlaying(); // process events if game isn't playing
}

bool Editor::gamePlaying()
{
	return _menuBar.gamePlaying();
}

LRESULT Editor::mainMenuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return _menuBar.processMsg(hWnd, message, wParam, lParam);
}





void Editor::initConsole()
{
	int hConHandle;
    long lStdHandle;
    FILE *filePtr;

	// Create console
    AllocConsole();

	// STD out to console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE); // get stdo handle
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT); // get file handle using stdo handle 
    filePtr = _fdopen( hConHandle, "w" ); // pointer to file handle writes to

    *stdout = *filePtr;
    setvbuf( stdout, NULL, _IONBF, 0 );

	//STD in to console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    filePtr = _fdopen( hConHandle, "r" );

    *stdin = *filePtr;
    setvbuf( stdin, NULL, _IONBF, 0 );

	// STD Error to console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    filePtr = _fdopen( hConHandle, "w" );

    *stderr = *filePtr;
    setvbuf( stderr, NULL, _IONBF, 0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    std::ios::sync_with_stdio();
}



int Editor::processTweakBarEvents(sf::Event* event)
{
	if(!_processTwEvents) return 0;

	int handled = 0;
    TwMouseAction mouseAction;
    int key = 0;
    static int s_KMod = 0;
    static bool s_PreventTextHandling = false;
    static int s_WheelPos = 0;

    if (event == NULL)
        return 0;

    switch (event->type)
    {
    case sf::Event::KeyPressed:
        s_PreventTextHandling = false;
        s_KMod = 0;
        if (event->key.shift)   s_KMod |= TW_KMOD_SHIFT;
        if (event->key.alt)     s_KMod |= TW_KMOD_ALT;
        if (event->key.control) s_KMod |= TW_KMOD_CTRL;
        key = 0;
        switch (event->key.code)
        {
		case sf::Keyboard::Escape:
            key = TW_KEY_ESCAPE;
            break;
        case sf::Keyboard::Return:
            key = TW_KEY_RETURN;
			_goMenu.refreshGameObjects(); // refresh objects in go menu whenever you press return
            break;
        case sf::Keyboard::Tab:
            key = TW_KEY_TAB;
            break;
		case sf::Keyboard::BackSpace:
            key = TW_KEY_BACKSPACE;
            break;
        case sf::Keyboard::PageUp:
            key = TW_KEY_PAGE_UP;
            break;
        case sf::Keyboard::PageDown:
            key = TW_KEY_PAGE_DOWN;
            break;
        case sf::Keyboard::Up:
            key = TW_KEY_UP;
            break;
        case sf::Keyboard::Down:
            key = TW_KEY_DOWN;
            break;
        case sf::Keyboard::Left:
            key = TW_KEY_LEFT;
            break;
        case sf::Keyboard::Right:
            key = TW_KEY_RIGHT;
            break;
        case sf::Keyboard::End:
            key = TW_KEY_END;
            break;
        case sf::Keyboard::Home:
            key = TW_KEY_HOME;
            break;
        case sf::Keyboard::Insert:
            key = TW_KEY_INSERT;
            break;
        case sf::Keyboard::Delete:
            key = TW_KEY_DELETE;
            break;
        case sf::Keyboard::Space:
            key = TW_KEY_SPACE;
            break;
        default:
            if (event->key.code >= sf::Keyboard::F1 && event->key.code <= sf::Keyboard::F15)
                key = TW_KEY_F1 + event->key.code - sf::Keyboard::F1;
            else if (s_KMod & TW_KMOD_ALT) 
            {
                if (event->key.code >= sf::Keyboard::A && event->key.code <= sf::Keyboard::Z)
                {
                    if (s_KMod & TW_KMOD_SHIFT)
                        key = 'A' + event->key.code - sf::Keyboard::A;
                    else
                        key = 'a' + event->key.code - sf::Keyboard::A;
                }
            }
        }
        if (key != 0) 
        {
            handled = TwKeyPressed(key, s_KMod);
            s_PreventTextHandling = true;
        }
        break;
    case sf::Event::KeyReleased:
        s_PreventTextHandling = false;
        s_KMod = 0;
        break;
    case sf::Event::TextEntered:
		_goMenu.refreshGameObjects(); // refresh objects in go menu whenever you enter some text into a param and press return
        if (!s_PreventTextHandling && event->text.unicode != 0 && (event->text.unicode & 0xFF00) == 0)
        {
            if ((event->text.unicode & 0xFF) < 32) // CTRL+letter
                handled = TwKeyPressed((event->text.unicode & 0xFF)+'a'-1, TW_KMOD_CTRL|s_KMod);
            else 
                handled = TwKeyPressed(event->text.unicode & 0xFF, 0);
        }
        s_PreventTextHandling = false;
        break;
    case sf::Event::MouseMoved:
		handled = TwMouseMotion(event->mouseMove.x, event->mouseMove.y);
        break;
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
		_goMenu.refreshGameObjects(); // refresh objects in go menu whenever you press or release mouse
        mouseAction = (event->type==sf::Event::MouseButtonPressed) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
        switch (event->mouseButton.button) 
        {
        case sf::Mouse::Left:
            handled = TwMouseButton(mouseAction, TW_MOUSE_LEFT);
            break;
        case sf::Mouse::Middle:
            handled = TwMouseButton(mouseAction, TW_MOUSE_MIDDLE);
            break;
        case sf::Mouse::Right:
            handled = TwMouseButton(mouseAction, TW_MOUSE_RIGHT);
            break;
        default:
            break;
        }
        break;
    case sf::Event::MouseWheelMoved:
        s_WheelPos += event->mouseWheel.delta;
        handled = TwMouseWheel(s_WheelPos);
        break;
    case sf::Event::Resized:
        // tell the new size to TweakBar
        TwWindowSize(event->size.width, event->size.height);
        // do not set 'handled', sf::Event::Resized may be also processed by the client application
        break;
    default:
        break;
    }

    return handled;
}