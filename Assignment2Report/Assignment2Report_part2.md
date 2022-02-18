# Assignment2Report_Part2

part1:

In this part we implemented the ambient color reflection and added it into the gui 

in the picture you gonna see we choose the light color to be gray color and the material color to be "darker gray" while spec and dif colors were 0

so in the result we got we had it be a dark gray since the values of "RGB" were lowered and they were equal so we got 

the result in the picture here

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/HW2_PART1.PNG)


part2:

in this part we computed flat shading with diffuse

the color of the material we chose was also red but we placed the light to be on the right side of the model

and thus you can see that his left side was "dark" since there was less lighting coming into this side however

the other side you can see the true color of the model and here is the picture of it

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/HW2_PART2.PNG)


part3:

here we computed Gourard shading and we computed it and the flat on the same picture (one each at a time)

the first picture you gonna see is the beethoven with the flat shading you can clearly see each triangle appearing especially in the head

and also in his hair however in the second picture where we used the gourard you can see less traingles and it being better looking 

flat pic:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/part3finalflat.PNG)

Gourard pic:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/part3finalgro.PNG)


part4:

here we implemented the light reflection we placed the light up almost of the model and thus you can see it reflecting that way 

here is the result we got  

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/part4.PNG)



part5:

this part is the implementation of phong  you can see in the results how there is less visable traingles that both of previes models

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/phong3.PNG)



part6:

directional light:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/directionallight.PNG)

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/directional2.PNG)


part7 :

in this part we show diffrent models and shadings

the first picture is model appearing in ambient and the second one appearing in reflection 

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/ambient+reflection.PNG)

and in this picture we of 2 models where the light is in the middle and not side of each moodel that is looking at the light is not dark

however the other side is the dark side

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/HM2Part7flat+flat.PNG)

here is another color of diffrent moodels where you can see how the light does not affect moodle of ambient how ever it does affect the 

other moodles

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/HW2FLAT+FLAT+AMBIENT.PNG)


here we showed a gif where the light start under the models and thus it's lighting them from down then we moved the possition of it upwards 

and you can see how the dark side of the models changed

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/gif1.gif)


part 8:

we first implemented guassian blur we built a kernel then we went on the pixles in the moodel we multipled the kernel values with the sorounding pixles of the current pixle 

we updated then the color buffer with the new color of each pixle the thing is that the moodle color is close but you can see the eyes blurring 

and some extra places in the face

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/guassian.PNG)


then we implemented the linear equation of the fog  and here is the few pics of the results we got

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/part8pic1.PNG)

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/part8pic2.PNG)

and here is a gif that shows how when we increase the depth the model get grayer 

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment2Report/gif2.gif)
