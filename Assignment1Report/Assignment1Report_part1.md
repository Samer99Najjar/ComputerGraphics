# Assignment1Report-part1

In this homework we implemented  the algorithm you tought us in class 
here is our implementation of the algorithm:
```
void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	int my_p1_x =p1.x;
	int my_p1_y= p1.y;
	int my_p2_x=p2.x;
	int my_p2_y=p2.y;
	int x = p1.x;
	int y = p1.y;

	int flag = 0;
	if (p1.x > p2.x) {
		x = p2.x;
		y = p2.y;
		my_p2_x = p1.x;
		my_p2_y = p1.y;
	}
	
	float delta_x = my_p2_x - x;
    float delta_y = my_p2_y - y;

	float a ;
	
	if (delta_x == 0) {
		flag = 1;
		if (delta_y < 0)
			delta_y = delta_y * (-1);
		while (delta_y >= 0) {
			if (y >= my_p2_y) {
				PutPixel(x, y, color);
				y--;

			}
			if (y <= my_p2_y) {
				PutPixel(x, y, color);
				y++;

			}
			delta_y--;
		}


	}
	if (flag == 0) {
		a = delta_y / delta_x;
	}
	


	if (delta_x < 0)
		delta_x = delta_x * (-1);
	if (delta_y < 0)
		delta_y = delta_y * (-1);
	//int  c = p1.y - delta_x * p1.x;
	

	if (flag==0 && a >= 0 && a < 1 ) {
		int e = -(delta_x);
		while (x < my_p2_x) {
			if (e >= 0) {
				y = y + 1;
				e = e - 2 * (delta_x);
			}
			PutPixel(x, y, color);
			x = x + 1;
			e = e + 2 * (delta_y);
		}
	}

	if (flag == 0 && a > -1 && a < 0) {
		int  e = -(delta_y);
		while (x <= my_p2_x) {

			if (e >= 0) {
				y = y - 1;
				e = e - 2 * (delta_x);
			}
			PutPixel(x, y, color);
			x = x + 1;
			e = e + 2 * (delta_y);
		}
	}

		if (flag == 0 && a >= 1) {
		
			int e = -(delta_y);
			while (y <= my_p2_y) {
				
				if (e >= 0) {
					x = x + 1;
					e = e - 2 * (delta_y);
				}
				PutPixel(x, y, color);
				y = y + 1;
				e = e + 2 * (delta_x);
			}
		}
		
		
			
		if (flag == 0 && a <= -1) {
			int  e = -(delta_y);
			while (y >= my_p2_y) {
				
				if (e >= 0) {
					x = x + 1;
					e = e - 2 * (delta_y);
				}
				PutPixel(x, y, color);
				y = y - 1;
				e = e + 2 * (delta_x);
			}
		}	
		
}
```
then  we did the sanity check and here is what we got from it :
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/sanitycheck.png)

afterwards we did drawing of out selves of the words(good game easy clap) GG EZ CLAP
here is the image for it 

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/ourimage.png)



and we did drawing a beaty star 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/star.png)


