#Welcome, Today i will make my first python game , it is pong and hopefully you will enjoy it

import turtle

wn = turtle.Screen()
wn.setup(width= 800, height = 600)
wn.bgcolor("black")
wn.tracer(1)
wn.title("Pong")

#Making the players

paddle_a = turtle.Turtle()
paddle_a.shape("square")
paddle_a.color("white")
paddle_a.speed(0)
paddle_a.penup()
paddle_a.goto(-360,0)
paddle_a.shapesize(stretch_wid=5,stretch_len=1)

paddle_b = turtle.Turtle()
paddle_b.shape("square")
paddle_b.color("white")
paddle_b.speed(0)
paddle_b.penup()
paddle_b.goto(360,0)
paddle_b.shapesize(stretch_wid=5,stretch_len=1)

#Making the ball

ball = turtle.Turtle()
ball.shape("square")
ball.color("white")
ball.speed(0)
ball.penup()
ball.goto(0,0)
ball.dx = 1
ball.dy = 1

#Defining the player movement

def paddle_a_up() :
    y = paddle_a.ycor()
    y += 20
    paddle_a.sety(y)

def paddle_a_down() :
    y = paddle_a.ycor()
    y -= 20
    paddle_a.sety(y)


def paddle_b_up() :
    y = paddle_b.ycor()
    y += 20
    paddle_b.sety(y)

def paddle_b_down() :
    y = paddle_b.ycor()
    y -= 20
    paddle_b.sety(y)

wn.listen()
wn.onkeypress(paddle_a_up,"w")
wn.onkeypress(paddle_a_down,"s")
wn.onkeypress(paddle_b_up,"Up")
wn.onkeypress(paddle_b_down,"Down")

#Main Loop of the game

while(1) :
    wn.update()

    #Ball Movement
    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)

    #Collision with borders management
    if (ball.ycor() > 290):
        ball.sety(290)
        ball.dy *= -1
    
    if (ball.ycor() < -290):
        ball.sety(-290)
        ball.dy *= -1

    if (ball.xcor() > 390):
        ball.goto(0,0)
        ball.dx *= -1

    if (ball.xcor() < -390):
        ball.goto(0,0)
        ball.dx *= -1
    
    #Collision with the paddle
    if(ball.xcor() > 340 and ball.xcor() < 350) and (ball.ycor() < paddle_b.ycor() + 40 and ball.ycor() > paddle_b.ycor() - 40) :
        ball.setx(340)
        ball.dx *= -1
    if(ball.xcor() > 340 and ball.xcor() < 350) and (ball.ycor() < paddle_a.ycor() + 40 and ball.ycor() > paddle_a.ycor() - 40) :
        ball.setx(340)
        ball.dx *= -1
    #Let test it 