/*
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

//chat gpt generated, あーー人生楽になる　あーわかりやすい

// CSI manipulations for cursor movement
#define CURSOR_UP "\033[A"
// #define CURSOR_BACKWARD(x) "\033[%dD"
// #define CURSOR_DOWN(x) "\033[%dB"
// #define CURSOR_FORWARD(x) "\033[%dC"
// #define CURSOR_BACKWARD(x) "\033[%dD"
// #define CURSOR_POSITION(x, y) "\033[%d;%dH"
// #define SAVE_CURSOR "\033[s"
// #define RESTORE_CURSOR "\033[u"

// Test code
int main() {
	char *line;
    // printf("Line 1\n");
    // printf("Line 2\n");
    // printf("Line 3\n");
    
    // Move the cursor up 2 lines
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
	}
    // printf(CURSOR_UP);
    // printf("exit\n");
	exit(0);
    
    // // Move the cursor forward 3 columns
    // printf(CURSOR_FORWARD(3));
    // printf("Moved forward 3 columns\n");
    
    // // Move the cursor to position (3, 3)
    // printf(CURSOR_POSITION(3, 3));
    // printf("Moved to position (3, 3)\n");
    
    // // Save the cursor position
    // printf(SAVE_CURSOR);
    // printf("Saved cursor position\n");
    
    // // Move the cursor down 1 line
    // printf(CURSOR_DOWN(1));
    // printf("Moved down 1 line\n");
    
    // // Restore the cursor position
    // printf(RESTORE_CURSOR);
    // printf("Restored cursor position\n");

    return 0;
}
*/

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char* input = readline("Enter text: ");
    printf("You entered: %s", input);
    
    // Replace the input line with new text
    // rl_replace_line("New line of text", 1);
    
    input = readline("Enter text again: ");
    // printf("You entered again: %s\n", input);
    
    free(input);
    return 0;
}