# Day 1 of my 8th attempt on making a Game Engine:

So, I managed to make this lil triangle so far, while understanding most of the stuff that's happening, also saving this to remember about how positions work in openGL:

> The first vertex is (-1,-1,0). This means that unless we transform it in some way, it will be displayed at (-1,-1) on the screen. What does this mean ? The screen origin is in the middle, X is on the right, as usual, and Y is up. This is what it gives on a wide screen

![it works!](./img/it%20works.png)

*few hours later*

I MANAGED TO MAKE A -w- FACE USING THIS SHIT :3

![-w-](./img/-w-.png)

*~4 more hours later*

I have made it bounce, and I'm proud of it. (this was such a pain to make, the triangle::place function mainly for some reason)

## Notes to self:
- Remember to initialize GLEW after the window gets activated and before you create any VAOs
- makefiles are a mess