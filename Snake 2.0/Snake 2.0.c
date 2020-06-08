#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct {
	int way;
	HWND hwnd;
	int x;
	int y;
}Snake;

typedef struct {
	HWND hwnd;
	int x;
	int y;
}Food;

typedef struct {
	int x;
	int y;
}Body;

typedef struct {
	char name[10];
	int y;
}Record;


#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
void sort (Record* tmp,int N);
void displayDia(HWND hWnd);
void DialogWin(HINSTANCE hInstance);
Food spawn_food();


HWND hEdit;
HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
HBITMAP	Imege ;
Record record_now;
Body* body;
Snake snake[2];
Food food;
int sizeSnake;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	int num = 0;
	static int flag = 0;
	switch(Message) {
	
		case WM_TIMER:{
			int tempX = snake[0].x;
			int tempY = snake[0].y;

			switch(snake[0].way){
				
				case UP:{
					
					snake[0].y -= 10;
					
					break;
				}
				
				case DOWN:{
					
					snake[0].y += 10;
					
					break;
				}
				
				case LEFT:{
					
					snake[0].x -= 10;
					
					break;
				}
				
				case RIGHT:{
					
					snake[0].x += 10;
					
					break;
				}		
			}
		
		int i;
		
	
		if(snake[0].y == -10) {
			snake[0].y = 410;
		}
		
		
		if(snake[0].y == 420){
			snake[0].y = 0;
		} 
		
		if(snake[0].x == -10) {
			snake[0].x = 620;
		}
		
		
		if(snake[0].x == 630){
			snake[0].x = 0;
		}
		

		snake[1].x = body[sizeSnake-1].x;
		snake[1].y = body[sizeSnake-1].y;
		
		for(i = sizeSnake - 1;i >= 1 ;i--){
			
			body[i].x = body[i-1].x;
			body[i].y = body[i-1].y;	
		}
	
	
		body[0].x = tempX;
		body[0].y = tempY;
		
		
		

		SetWindowPos(snake[0].hwnd,0,snake[0].x,snake[0].y,10,10,SWP_SHOWWINDOW);

		SetWindowPos(snake[1].hwnd,0,snake[1].x,snake[1].y,10,10,SWP_SHOWWINDOW);

		hdc=GetDC(hwnd);
		
		for(i = 0;i < sizeSnake;i++){
			Rectangle(hdc,body[i].x,body[i].y,(body[i].x + 10),(body[i].y + 10));
		}
		


		if(snake[0].x == food.x && snake[0].y == food.y){
		
			sizeSnake++;	
			
			record_now.y += 100;
						
			body = (Body*)realloc(body,sizeof(Body) * sizeSnake);			

			spawn_food();
			SetWindowPos(food.hwnd,0,food.x,food.y,10,10,SWP_SHOWWINDOW);

		}
		
		if(snake[0].x == snake[1].x && snake[0].y == snake[1].y){
				
					FILE* pOut = fopen("record.bin","ab");
	
					if (!pOut){
						
	     				return 1;
	   				}
	   				
	   				if (fwrite(&record_now,sizeof(Record),1,pOut) != 1){
				       
				         fclose(pOut);
				         return 1;
	     			 }
					fflush(pOut);
					displayDia(hwnd);
					KillTimer(hwnd, 1);
					for(i = 0;i < sizeSnake;i++){
								SetWindowPos(snake[1].hwnd,0,body[i].x,body[i].y,10,10,SWP_SHOWWINDOW);
					}
					fclose(pOut);

		}
		
		for(i = 2;i < sizeSnake;i++){
			if(snake[0].x == body[i].x && snake[0].y == body[i].y){
					int i;
					FILE* pOut = fopen("record.bin","ab");
	
					if (!pOut){
						
	     				return 1;
	   				}
	   				
	   				if (fwrite(&record_now,sizeof(Record),1,pOut) != 1){
				       
				         fclose(pOut);
				         return 1;
	     			 }
	   				fflush(pOut);
					displayDia(hwnd);
					KillTimer(hwnd, 1);
					for(i = 0;i < sizeSnake;i++){
								SetWindowPos(snake[1].hwnd,0,body[i].x,body[i].y,10,10,SWP_SHOWWINDOW);
					}
					
					fclose(pOut);

			}
			
			
		}
		
		flag = 0;
		
			break;
		}
			
		case WM_KEYDOWN:{
			
			char str [40];
			
			itoa(snake[0].y,str,10);
			
			
			strcat(str, " : y");
			
			
			SetWindowText(hwnd,(LPCTSTR)str);

				unsigned int key = wParam;
			if(flag == 0){
				
			switch(key){
				case 87:{

					if(snake[0].way != DOWN)
					snake[0].way = UP;
					flag = 1;
					
					break;
				}
				case 83:{
					
					if(snake[0].way != UP)
					snake[0].way = DOWN;
					
					flag = 1;
					
					
					break;
				}	
				
				case 68:{
					if(snake[0].way != LEFT)
					snake[0].way = RIGHT;
					
					flag = 1;
					
					
					break;
				}	
				
				case 65:{
					if(snake[0].way != RIGHT)
					snake[0].way = LEFT;
					
					flag = 1;
					
									
					break;
				}		
				case 38:{

					if(snake[0].way != DOWN)
					snake[0].way = UP;
					flag = 1;
					
					break;
				}
				case 40:{
					
					if(snake[0].way != UP)
					snake[0].way = DOWN;
					
					flag = 1;
					
					
					break;
				}	
				
				case 39:{
					if(snake[0].way != LEFT)
					snake[0].way = RIGHT;
					
					flag = 1;
					
					
					break;
				}	
				
				case 37:{
					if(snake[0].way != RIGHT)
					snake[0].way = LEFT;
					
					flag = 1;
					
									
					break;
				}		
			}
		}
		
		
			break;
		}
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE:{
			sizeSnake = 1;
				
			snake[0].way = RIGHT;
			snake[0].x = 100;
			snake[0].y = 100;
			snake[0].hwnd = CreateWindowW( L"Static" ,0,WS_VISIBLE | WS_CHILD | WS_BORDER ,snake[0].x,snake[0].y,10,10,hwnd,0,0,0);
		
		
			
			body = (Body*)malloc(sizeof(Body));
			body[0].x = 90;
			body[0].y = 100;
		
		
			
			snake[1].x = 80;
			snake[1].y = 100;
			snake[1].hwnd = CreateWindowW( L"Static" ,0,WS_VISIBLE | WS_CHILD | WS_BORDER ,snake[1].x,snake[1].y,10,10,hwnd,0,0,0);
			
			
			
			spawn_food();
			food.hwnd = CreateWindowW( L"Static" ,0,WS_VISIBLE | WS_CHILD |WS_BORDER ,food.x,food.y,10,10,hwnd,0,0,0);
			displayDia(hwnd);
			
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */

	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	DialogWin(hInstance);

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		453, /* height */
		NULL,NULL,hInstance,NULL);



	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	

	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	KillTimer(hwnd, 1);
	return msg.wParam;
}


Food spawn_food(){
	srand(time(0));
	int i, flag;
	for(;;){
		flag = 0;
		food.x = rand()% 610;
		food.y = rand()% 420;	
		
		if(	food.x % 10 == 0 && food.y % 10 == 0 ){
		for(i = 0;i < 2;i++)
		if(food.y == snake[i].y && food.x == snake[i].x)
		flag ++;
		
		for(i = 0;i < sizeSnake; i++)
		if(food.y == body[i].y && food.x == body[i].x)
		flag++;
		
		if(flag == 0)
		return;
		}
		
	}
}







LRESULT CALLBACK  DialogWinPro(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp){
	
	

	switch (msg){
		case WM_COMMAND:
			 
			 switch(wp){
			 	case 1:{
			 		
			 			GetWindowText(hEdit,record_now.name,10);
			 			
			 			if(record_now.name[0] == '\0') 	strcpy(record_now.name,"no name");
						
						snake[0].way = RIGHT;
						snake[0].x = 100;
						snake[0].y = 100;
						
						body = (Body*)realloc(body,sizeof(Body));
						body[0].x = 90;
						body[0].y = 100;
						
						
						snake[1].x = 80;
						snake[1].y = 100;
						
			 			SetWindowPos(snake[0].hwnd,0,snake[0].x,snake[0].y,10,10,SWP_SHOWWINDOW);
						SetWindowPos(snake[1].hwnd,0,snake[1].x,snake[1].y,10,10,SWP_SHOWWINDOW);
			 			
			 			sizeSnake = 1;
						record_now.y = 0;
					 	SetTimer(hwnd,1,100,0); // скорость передвіженія
						EnableWindow(hwnd,1);
						DestroyWindow(hWnd);
						
					break;
				 }
				 case 2:{
				 	DestroyWindow(hwnd);
				 	DestroyWindow(hWnd);
					break;
				 }
			 }
			
			break;
			
		
		case WM_CLOSE:
			
						snake[0].way = RIGHT;
						snake[0].x = 100;
						snake[0].y = 100;
						
						body = (Body*)realloc(body,sizeof(Body));
						body[0].x = 90;
						body[0].y = 100;
						
						
						snake[1].x = 80;
						snake[1].y = 100;
						
			 			SetWindowPos(snake[0].hwnd,0,snake[0].x,snake[0].y,10,10,SWP_SHOWWINDOW);
						SetWindowPos(snake[1].hwnd,0,snake[1].x,snake[1].y,10,10,SWP_SHOWWINDOW);
			 			
			 			sizeSnake = 1;
						record_now.y = 0;
						
						
				strcpy(record_now.name,"no name");
				SetTimer(hwnd,1,100,0);
				EnableWindow(hwnd,1);
				DestroyWindow(hWnd);
			
			break;
			
		default:
				return DefWindowProcW(hWnd,msg,wp,lp);
		
		
	}
}





void DialogWin(HINSTANCE hInstance){
	WNDCLASSW dia = {0};
	dia.hbrBackground = (HBRUSH)(COLOR_WINDOW+24);
	dia.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	dia.hInstance	 = hInstance; 
	dia.lpszClassName = L"DialogWinClass";
	dia.lpfnWndProc	 = DialogWinPro;
	RegisterClassW(&dia);
	}

void displayDia(HWND hWnd){

	int i;
	
	char str [1000];
	str[0] = '\0';
	char buf[10];
	
	
	FILE* pIn = fopen("record.bin","rb");
	if(pIn){
		

	fseek(pIn,0,SEEK_END);
	int counter = ftell(pIn)/sizeof(Record);
	fseek(pIn,0,SEEK_SET);
	

	Record *tmp = (Record*)malloc(counter*sizeof(Record));
	
	fseek(pIn,0,SEEK_SET);
	for(i = 0; i < counter;i++){
		if(fread(&tmp[i],sizeof(Record),1,pIn )!= 1){
			fclose(pIn);
		}
	}
	
	sort(tmp,counter);
	fclose(pIn);
	
	if(counter > 10){
		counter = 10;
	}
	
	pIn = fopen("record.bin","wb");
	
		for(i = 0;i < counter;i++){
			
	   		if (fwrite(&tmp[i],sizeof(Record),1,pIn) != 1){
					       
			       fclose(pIn);
			
	     	}
		}
	

	for(i = 0;i < counter;i++){
		
			itoa(i+1,buf,10);
			
			strcat(str,buf);
		
			strcat(str,". ");
		
			strcat(str,tmp[i].name);
			
			strcat(str," : ");
			
			itoa(tmp[i].y,buf,10);
	
			strcat(str,buf);
			
			strcat(str,"\n");


		}
		
		free(tmp);
	
	}else strcpy(str,"Пусто!");

	str[strlen(str)] = '\0';
	
	HWND hDlg = CreateWindowW(L"DialogWinClass",L"Dialog",WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,200,200,350,200,hWnd,0,0,0);
	
	hEdit = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER ,19,31,100,20,hDlg,0,0,0);
	
	CreateWindowW(L"Button",L"Start",WS_VISIBLE | WS_CHILD,40,110,60,20,hDlg,(HMENU)1,0,0);
	CreateWindowW(L"Button",L"Exit",WS_VISIBLE | WS_CHILD,40,130,60,20,hDlg,(HMENU)2,0,0);

	
	
	HWND hOut = CreateWindowW( L"Static" ,0,WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER ,142,0,200,170,hDlg,(HMENU)1,0,0);
	
	SetWindowText(hOut,str);
	EnableWindow(hWnd,0);
	fclose(pIn);
}





void sort (Record* tmp,int N){
	int i,j;
	
	for(i = 0;i < N - 1;i++){
		for(j = 0;j < N-1-i;j++){
			
			if(tmp[j].y < tmp[j+1].y){
					
				Record tmp1 = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j +1] = tmp1;
				
			} 
		}
	}	
}

