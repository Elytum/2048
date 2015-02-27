#include <stdio.h>
#define BUFF_SIZE 2048
#include <stdio.h>
#include <ncurses.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#define WIDTH 30
#define HEIGHT 10
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define ESC 27

int startx = 0;
int starty = 0;

char *choices[] = { 
	"Nouvelle partie",
	"Options",
	"Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int ft_continue(int map[][BUFF_SIZE], char sx, char sy)
{
	int r;

	if (!(!(*map)[0] || !(*map)[1] || !(*map)[2] || !(*map)[3] ||
		  !(*map)[4] || !(*map)[5] || !(*map)[6] || !(*map)[7] ||
		  !(*map)[8]))
		return (0);
	while (1)
	{
		r = rand() % 32;
		if ((*map)[r % 16] == 0)
		{
			(*map)[r % 16] = (r / 16) ? 2 : 4;
			break ;
		}
	}
	return ((!(*map)[0] || !(*map)[1] || !(*map)[2] || !(*map)[3] ||
			 !(*map)[4] || !(*map)[5] || !(*map)[6] || !(*map)[7] ||
			 !(*map)[8]) || ((*map)[0] == (*map)[1] || (*map)[1] == (*map)[2] ||
							 (*map)[3] == (*map)[4] || (*map)[4] == (*map)[5] ||
							 (*map)[6] == (*map)[7] || (*map)[7] == (*map)[8] ||
							 (*map)[0] == (*map)[3] || (*map)[3] == (*map)[6] ||
							 (*map)[1] == (*map)[4] || (*map)[4] == (*map)[7] ||
							 (*map)[2] == (*map)[5] || (*map)[5] == (*map)[8]));
}


void ft_putnbr(int n)
{
	char c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write (1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write (1, &c, 1);
	}
}

void ft_drawmap(int map[BUFF_SIZE], char sx, char sy)
{
	int x;
	int y;

	write(1, "\nThe map is : \n", 15);
	y = 0;
	while (y < sy)
	{
		x = 0;
		while (x < sx)
		{
			ft_putnbr(map[y * sy + x++]);
			write (1, "\t", 1);
		}
		write (1, "\n", 1);
		y++;
	}
}

char ft_move(int map[][BUFF_SIZE], char past, char next)
{
	write (1, "\nMOVE\n", 6);
	if ((*map)[next])
	{
		(*map)[next] *= 2;
		(*map)[past] = 0;
	}
	else
	{
		(*map)[next] = (*map)[past];
		(*map)[past] = 0;
	}
	return (1);
}

char ft_up(int map[][BUFF_SIZE], char sx, char sy)
{
	char l;
	char re;
	char x;
	char y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		y = 1;
		while (y < sy)
		{
			x = 0;
			while (x < sx)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * (y - 1) + x] == 0 ||
										   ((*map)[sx * y + x] == (*map)[sx * (y - 1) + x])) && (l = 1))
					re = ft_move(map, sx * y + x, sx * (y - 1) + x);
				x++;
			}
			y++;
		}
	}
	return (re);
}

char ft_down(int map[][BUFF_SIZE], char sx, char sy)
{
	char l;
	char re;
	char x;
	char y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		y = sy - 2;
		while (y >= 0)
		{
			x = 0;
			while (x < sx)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * (y + 1) + x] == 0 ||
										   ((*map)[sx * y + x] == (*map)[sx * (y + 1) + x])) && (l = 1))
					re = ft_move(map, sx * y + x, sx * (y + 1) + x);
				x++;
			}
			y--;
		}
	}
	return (re);
}

char ft_left(int map[][BUFF_SIZE], char sx, char sy)
{
	char l;
	char re;
	char x;
	char y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		x = 1;
		while (x < sx)
		{
			y = 0;
			while (y < sy)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * y + x - 1] == 0 ||
										   ((*map)[sx * y + x] == (*map)[sx * y + x - 1])) && (l = 1))
					re = ft_move(map, sx * y + x, sx * y + x - 1);
				y++;
			}
			x++;
		}
	}
	return (re);
}

char ft_right(int map[][BUFF_SIZE], char sx, char sy)
{
	char l;
	char re;
	char x;
	char y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		x = sx - 2;
		while (x >= 0)
		{
			y = 0;
			while (y < sy)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * y + x + 1] == 0 ||
										   ((*map)[sx * y + x] == (*map)[sx * y + x + 1])) && (l = 1))
					re = ft_move(map, sx * y + x, sx * y + x + 1);
				y++;
			}
			x--;
		}
	}
	return (re);
}
void handle_winch(int sig){

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    COLS = w.ws_col;
    LINES = w.ws_row;
	int i;
    wresize(stdscr, LINES, COLS);
    clear();
    i = 0;
    mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
    while (i < COLS)
    {
        mvaddch(1, i, '*');
        i++;
    }
    refresh();
}
void print_menu(WINDOW *menu_win, int highlight);
int main(void)
{
	int map[BUFF_SIZE] = {0};
	char buff[2] = {0};
	int check;
	int play;
    struct sigaction sa;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	initscr();
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = handle_winch;
    sigaction(SIGWINCH, &sa, NULL);
	clear();
	noecho();
	cbreak();/* Line buffering disabled. pass on everything */
	startx = (WIDTH) / 2;//startx = (WIDTH) / 2;
	starty = (HEIGHT) / 2;//starty = (HEIGHT) / 2;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	//mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();

	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		/*switch(c)
		{
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		} */
		if (*buff == KEY_UP)
		{
			if(highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		}
		if (*buff == KEY_DOWN)
		{
			if(highlight == n_choices)
				highlight = 1;
			else 
				++highlight;
			break;			
		}
		if (*buff == 10)
		{
			choice = highlight;
			break ;
		}
		else
		{
			refresh();
			break ;
		}


		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	endwin();
	check = 0;
	play = 1;
	ft_continue(&map, 4, 4);
	ft_drawmap(map, 4, 4);
	while (play)
	{
		read(1, buff, 2);
		if (*buff == 'w')
			check = ft_up(&map, 4, 4);
		else if (*buff == 's')
			check = ft_down(&map, 4, 4);
		else if (*buff == 'a')
			check = ft_left(&map, 4, 4);
		else if (*buff == 'd')
			check = ft_right(&map, 4, 4);
		if (check && !(check = 0))
			play = ft_continue(&map, 4, 4);
		ft_drawmap(map, 4, 4);
		buff[0] = '\0';
	}
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
