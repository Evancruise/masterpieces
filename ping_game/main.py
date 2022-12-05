from winreg import KEY_WOW64_32KEY
import pygame
#from pygame.locals import *
#import os
import random
#import math
import time
import json

from pygame.locals import *
from pygame import *
from config import *
from pongGame import pongGame
from text import InputBox

# Initialize game engine, screen and clock
pygame.init()
#pygame.mixer.init()
screen = pygame.display.set_mode(SCREENSIZE)
pygame.mouse.set_visible(SHOW_MOUSE)
pygame.display.set_caption(TITLE)
clock = pygame.time.Clock()

obstacles_pos = [(400, 200, 100, 400), (100, 500, 20, 300)]

def load_scores(file):
    # open a json file containing scores and return dict
    with open(file) as f:
        return json.load(f)

def show_high_scores(screen, high_scores):
    # clear the screen
    screen.fill(BACKGROUND)
    pygame.display.update()

    pause = 0

    # generate heading msg, position, blit
    high_score_heading = game_font.render('HIGH SCORES', False, INTERFACE_PRI)
    text_height = high_score_heading.get_height()
    text_y_pos_multiplier = 7
    wide_score = 0
    high_score_heading_pos = (SCREENSIZE[0] // 2 - (high_score_heading.get_width() // 2),
                            SCREENSIZE[1] // 2 - (text_height * text_y_pos_multiplier))
    screen.blit(high_score_heading, high_score_heading_pos)
    text_y_pos_multiplier -= 2

    # loop through dict 'high_scores'
    for pos, record in high_scores.items():
        if len(pos) == 1:
            pos = " " + pos
        record["score"] = str(record["score"])
        if wide_score <= len(record["score"]):
            wide_score = len(record["score"])
        else:
            record["score"] = (" " * (wide_score - len(record["score"]))) + record["score"]
        score_text = game_font.render(pos + " " + record["name"] + " " + record["score"], False, INTERFACE_SEC)
        score_text_pos = (SCREENSIZE[0] // 2 - (score_text.get_width() // 2),
                            SCREENSIZE[1] // 2 - (text_height * text_y_pos_multiplier))
        screen.blit(score_text, score_text_pos)
        text_y_pos_multiplier -= 1
    
    # generate instruction msg, position, blit
    text_y_pos_multiplier -= 1
    high_score_msg = game_font.render('PRESS \'SPACE\' TO CONTINUE', False, INTERFACE_SEC)
    high_score_msg_pos = (SCREENSIZE[0] // 2 - (high_score_msg.get_width() // 2),
                            SCREENSIZE[1] // 2 - (text_height * text_y_pos_multiplier))
    screen.blit(high_score_msg, high_score_msg_pos)

    # update the display
    pygame.display.update()

    # infinite loop to listen / wait for continue
    while pause == 0:
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.key == K_SPACE:
                    pause = -1

class Player(pygame.sprite.Sprite):
    """
    Spawn a player
    """

    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.movex = 0
        self.movey = 0
        self.frame = 0
        self.images = []

def main():

    global current_game_state

    # load high-score file
    high_scores = load_scores("scores.json")
    x, y = 150, 120

    # set the random seed - produces more random trajectories
    random.seed()

    # set the game running
    current_game_state = GAME_STATE_RUNNING

    show_high_scores(screen, high_scores)

    LEVEL = 0

    # setup the MCGAME AI
    ponggame = pongGame(1, high_scores["1"]["score"])

    while True:
        # write event handlers here
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    ponggame.exit_game(screen)
                if event.key == K_p:
                    ponggame.pause_game(screen)
                if event.key == K_s:
                    if PLAYER1_COOR[1] >= SCREENSIZE[1]-BAR_LENGTH:
                        PLAYER1_COOR[1] = SCREENSIZE[1]-BAR_LENGTH
                    else:
                        PLAYER1_COOR[1] += 20
                if event.key == K_w:
                    if PLAYER1_COOR[1] == 0:
                        PLAYER1_COOR[1] = 0
                    else:
                        PLAYER1_COOR[1] -= 20
                if event.key == K_KP2:
                    if PLAYER2_COOR[1] >= SCREENSIZE[1]-BAR_LENGTH:
                        PLAYER2_COOR[1] = SCREENSIZE[1]-BAR_LENGTH
                    else:
                        PLAYER2_COOR[1] += 20
                if event.key == K_KP8:
                    if PLAYER2_COOR[1] == 0:
                        PLAYER2_COOR[1] = 0
                    else:
                        PLAYER2_COOR[1] -= 20

        # clear the screen before drawing
        screen.fill(BACKGROUND)

        # --- Draw the interface
        ponggame.draw_players(screen, (PLAYER1_COOR[0], PLAYER1_COOR[1], BAR_WIDTH, BAR_LENGTH))
        ponggame.draw_players(screen, (PLAYER2_COOR[0], PLAYER2_COOR[1], BAR_WIDTH, BAR_LENGTH))

        x, y = ponggame.update_coords(x, y, screen, PLAYER1_COOR, PLAYER2_COOR)
        ponggame.draw(screen, x, y) 

        pygame.display.update()

        if current_game_state == GAME_STATE_NEW_LEVEL:
            time.sleep(0.0001)
            current_game_state = GAME_STATE_RUNNING

        # hold for few seconds before proceeding to high-score or back to menu or game over splash
        if current_game_state == GAME_STATE_OVER:
            input_box = InputBox(100, 100, 140, 32)
            while input_box.check_finished() == False:
                for event in pygame.event.get():
                    input_box.handle_event(event)
                input_box.update()
                input_box.draw(screen)
                
            current_game_state = GAME_STATE_MENU
        
        if current_game_state == GAME_STATE_OVER:
            ponggame.game_over(screen)

        # run at pre-set fps
        clock.tick(FPS)

    #while(1) :
        #screen.update()

        #Ball Movement
        #ponggame.ball.setx(ponggame.ball.xcor() + ponggame.ball.dx)
        #ponggame.ball.sety(ponggame.ball.ycor() + ponggame.ball.dy)

if __name__ == '__main__':
    main()