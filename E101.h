
void stop(int);
int init();
int take_picture();
int save_picture(char fn[5]);
char get_pixel( int row,int col, int color);
int set_pixel(int row, int col, char red, char green,char blue);
void convert_camera_to_screen();
int open_screen_stream();
int close_screen_stream();
int update_screen();
int display_picture(int delay_sec,int delay_usec);
int set_motor(int motor,int speed);
int sleep1(int sec, int usec);
int select_IO(int chan, int direct);
int write_digital(int chan,char level);
int read_digital(int chan);
int read_analog(int in_ch_adc);
int set_PWM(int chan, int value);
int set_PWM_frequency(int chan, int freq);
int set_servo(int chan, int value);
int connect_to_server( char server_addr[15],int port);
int send_to_server(char message[24]);
int receive_from_server(char message[24]);

