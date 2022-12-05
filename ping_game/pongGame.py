import pygame
import random
import turtle
from config import *
from pygame import *

class pongGame():
    def __init__(self, difficulty = 1, high_score = 0):
        self.player_score = 0
        self.high_score = high_score
        self.high_score_text = game_font.render('HIGH: {}'.format(self.high_score), False, INTERFACE_SEC)
        self.high_score_text_pos = SCREENSIZE[0] - self.high_score_text.get_width() - 5
        self.ground_level = SCREENSIZE[1] - GROUND_LEVEL
        self.x = 150
        self.y = 120
        self.color = DEFENCE
        self.dx = 1
        self.dy = 1
    
    def pause_game(self, screen):
        pause = 0
    
        # pause music / sfx
        pygame.mixer.pause()

        # display message that game is paused
        pause_msg = game_font.render('GAME PAUSED', False, INTERFACE_SEC)
        confirm_msg = game_font.render('PRESS \'P\' TO RESUME', False, INTERFACE_SEC)
        pause_msg_pos = (SCREENSIZE[0] // 2 - (pause_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (pause_msg.get_height() // 2))
        confirm_msg_pos = (SCREENSIZE[0] // 2 - (confirm_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (confirm_msg.get_height() // 2) + pause_msg.get_height())
        screen.blit(pause_msg, pause_msg_pos)
        screen.blit(confirm_msg, confirm_msg_pos)
        pygame.display.update()

        # wait for player to un-pause
        while pause == 0:
            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    if event.key == K_p:
                        pause = -1

        # resume music
        pygame.mixer.unpause()
    ''''
    # game over - all cities destroyed
    def game_over(self, screen):
        # display prompt for next level and give short pause
        screen.fill(BACKGROUND)

        continue_ = 0

        game_over_msg = game_font.render('Game Over (Press \'R\' to continue)', False, INTERFACE_SEC)
        # score_msg = game_font.render('SCORE: {}'.format(self.player_score), False, INTERFACE_SEC)
        game_over_msg_pos = (SCREENSIZE[0] // 2 - (game_over_msg.get_width() // 2),
                            SCREENSIZE[1] // 2 - (game_over_msg.get_height() // 2))
        # score_msg_pos = (SCREENSIZE[0] // 2 - (score_msg.get_width() // 2),
        #                    SCREENSIZE[1] // 2 - (score_msg.get_height() // 2) + game_over_msg.get_height())
        screen.blit(game_over_msg, game_over_msg_pos)
        # screen.blit(score_msg, score_msg_pos)
        pygame.display.update()

        while continue_ == 0:
            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    if event.key == K_r:
                        self.resume_game(screen)
                    else:
                        continue_ = -1
                        exit()
        
        # resume music ifplayer not exiting
        pygame.mixer.unpause()
    '''

    def game_over(self, screen):

        screen.fill(BACKGROUND)
        pygame.display.update()

        pause = 0
    
        # pause music / sfx
        pygame.mixer.pause()

        # display message to confirm exit
        exit_msg = game_font.render('Game Over!! SCORE: {}'.format(self.player_score), False, INTERFACE_SEC)
        question_msg = game_font.render('Want to play again?', False, INTERFACE_SEC)
        confirm_msg = game_font.render('(Y/N)', False, INTERFACE_SEC)

        exit_msg_pos = (SCREENSIZE[0] // 2 - (exit_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (exit_msg.get_height() // 2))
        question_msg_pos = (SCREENSIZE[0] // 2 - (question_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (question_msg.get_height() // 2)+ exit_msg.get_height()) 
   
        confirm_msg_pos = (SCREENSIZE[0] // 2 - (confirm_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (confirm_msg.get_height() // 2) + exit_msg.get_height() + question_msg.get_height() )

        screen.blit(exit_msg, exit_msg_pos)
        screen.blit(question_msg, question_msg_pos)
        screen.blit(confirm_msg, confirm_msg_pos)
        pygame.display.update()

        # wait for player to confirm exit or not
        while pause == 0:
            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    if event.key == K_y:
                        pause = -1
                        from main import main
                        main()
                    if event.key == K_n:
                        exit()

        # resume music ifplayer not exiting
        pygame.mixer.unpause()


    def exit_game(self, screen):
        # clear the screen
        screen.fill(BACKGROUND)
        pygame.display.update()

        pause = 0
    
        # pause music / sfx
        pygame.mixer.pause()

        # display message to confirm exit
        exit_msg = game_font.render('Quitting ... ', False, INTERFACE_SEC)
        question_msg = game_font.render('Are You Sure?', False, INTERFACE_SEC)
        confirm_msg = game_font.render('(Y/N)', False, INTERFACE_SEC)
   
        exit_msg_pos = (SCREENSIZE[0] // 2 - (exit_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (exit_msg.get_height() // 2))
    
        question_msg_pos = (SCREENSIZE[0] // 2 - (question_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (question_msg.get_height() // 2)+ exit_msg.get_height()) 
   
        confirm_msg_pos = (SCREENSIZE[0] // 2 - (confirm_msg.get_width() // 2),
                        SCREENSIZE[1] // 2 - (confirm_msg.get_height() // 2) + exit_msg.get_height() + question_msg.get_height() )
    
        screen.blit(exit_msg, exit_msg_pos)
        screen.blit(question_msg, question_msg_pos)
        screen.blit(confirm_msg, confirm_msg_pos)
        pygame.display.update()

        # wait for player to confirm exit or not
        while pause == 0:
            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    if event.key == K_y:
                        exit()
                    if event.key == K_n:
                        pause = -1

        # resume music ifplayer not exiting
        pygame.mixer.unpause()
    
    def draw(self, screen, x, y):
        # draw the HUD, score, etc
        pygame.draw.circle(screen, self.color, (x, y), 8)
        pygame.draw.line(screen, INTERFACE_PRI, [0, SKY_LEVEL], [SCREENSIZE[0], SKY_LEVEL], 2)
        # pygame.draw.rect(screen, INTERFACE_PRI, (0, SCREENSIZE[1] - GROUND_LEVEL, SCREENSIZE[0], SCREENSIZE[1]))
        score_text = game_font.render('SCORE: {}'.format(self.player_score), False, INTERFACE_SEC)
        screen.blit(score_text, (5, 10))
        screen.blit(self.high_score_text, (self.high_score_text_pos, 10))
        # TBC - draw the remaining ammo
    
    def draw_players(self, screen, pos):
        pygame.draw.rect(screen, INTERFACE_PRI, pos)

    def update_coords(self, x, y, screen, pos1, pos2):
        
        #pygame.draw.circle(screen, self.color, (pos1[0], pos1[1]), 8)
        #pygame.draw.circle(screen, self.color, (pos2[0], pos2[1]), 8)
        #pygame.draw.circle(screen, self.color, (SCREENSIZE[0] - DIS_TO_BORDER, pos2[1]), 8)

        if (x == DIS_TO_BORDER + BAR_WIDTH and y >= pos1[1] and y <= pos1[1] + BAR_LENGTH):
            if self.dx == -1:
                self.player_score += 1
                self.dx = 1
        
        if (x == SCREENSIZE[0] - DIS_TO_BORDER and y >= pos2[1] and y <= pos2[1] + BAR_LENGTH):
            if self.dx == 1:
                self.player_score += 1
                self.dx = -1

        if x < 0:
            # self.dx = 1
            self.game_over(screen)

        if x > SCREENSIZE[0]:
            # self.dx = -1
            self.game_over(screen)
        
        if y < 0:
            self.dy = 1
        if y > SCREENSIZE[1]:
            self.dy = -1

        return x + self.dx, y + self.dy
    
