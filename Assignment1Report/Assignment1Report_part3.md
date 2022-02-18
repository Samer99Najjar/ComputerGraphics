# Assignment1Report-part1

part 1:

we implemented the orthographic projection and here is 2 screen shots of results we got 

the first picture here we translated the camera and then we moved it to the right a bit and here is what we got
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/1.1.PNG)

afterwards we translated the camera then we turned left a bit and then we went down in the camera and this is what we got 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/1.2.PNG)

part 2 :

here we changed the window size and we still got the moodle in the middle  first of all here is a picture of how it appears before chaning anything

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/2.1.PNG)


afterwards we decreased the width of the window size and here is the result we got 

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/2.2.PNG)

and at last we did out sanity check we kept decreasing the window size until it became a small window that just fit the moodle and we still saw 

that the moodle was in the middle of the screen even when it was to small so we knew what we did was right and here what we got

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/2.3.PNG)

part3:

in this part we first  we first translated and rotated the moodle (frametranslation) and as you can see the axis move and translate with the moodle 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/3.1.1.gif)

and then we translated the the world arround the object and as you can see the axises didn't move only the moodle did 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/3.2.2.gif)

part4:

here we did first a local transform and after we did world rotate around Z axis and here what we got
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/4.1.1.gif)

after it we did world translate and then we did local rotate around Z axis and here is what we got

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/4.2.2.gif)

part5:

first of all we added the bounding box  and here is the exmaple of it on the bunny mesh :
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/5.1.PNG)

after it we added normal vertices and here is the result we got 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/5.2.PNG)

after we added the normal faces and here is the result we got 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/5.3.PNG)

after we did a sanity check where we rotated the the mesh around all axises and we also translated around all axises  it and we the box and the normals moved with it 

like we see in this screenshot
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/5sanitycheck.PNG)

part6:

first here is an image of orth projection
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/6.1orth.PNG)

and here is an image of pres projection
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/6.2per.PNG)

we can see clear diffrences like in the pres it's more like 3D image it's thinner taller compared to the orth 

part7:

here is the first screenshot after we zoomed the mesh out
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/7.1.PNG)

and here is the result of zooming in 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/7.2.PNG)

part8:

here is this video we translated the moodle to the edge of the screen then we did local rotate around y axis and then rotate y around world y axis 

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/8.gif)


part9:

we choose a=20 so by looking at point (20,20,20) here is the result we get
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/9.20.PNG)

part10:

here we translate the camera using mouse right click and left click :

the way it was done by calculating the inverse of the matrxies before hand and multiplying it with a translate matrix from the left


![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/10.gif)

part11:

here we show in this GIF that we have a camera on 2 models we make transformations on the camera  then we add new camera pick the new camera

and then we make new transformations on the new camera and both of the models are "moving" with it 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/10.51.gif)

part12:

our model local transofrmation gui:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/12.1.PNG)

our model world transformation gui:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/12.2.PNG)

our camera local transformation gui:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/12.3.PNG)

our camera world transformation gui:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/12.4.PNG)

part13:

we added features to allow the user to rotate the camera arrounr axisses (x ,y ,z) by pressing the x y z buttons like you can see in the vid

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment1Report/13.gif)

