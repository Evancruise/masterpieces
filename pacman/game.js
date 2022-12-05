const canvas = document.getElementById("canvas");
const canvasContext = canvas.getContext("2d");
const pacmanFrames = document.getElementById("animation");
// const bulletFrames = document.getElementById("bullet");
const ghostFrames = document.getElementById("ghosts");

let createRect = (x, y, width, height, color) => {
    canvasContext.fillStyle = color;
    canvasContext.fillRect(x, y, width, height);
};

let createCircle = (x, y, radius, color) => {
    canvasContext.fillStyle = color;
    canvasContext.beginPath();
    canvasContext.arc(x + 0.9999, y + 0.9999, radius, 0, 2 * Math.PI);
    canvasContext.fill();
};

var start_time = new Date().getTime();
var current_time;
var t;

const DIRECTION_RIGHT = 4;
const DIRECTION_UP = 3;
const DIRECTION_LEFT = 2;
const DIRECTION_BOTTOM = 1;
let lives = 5;
let ghostCount = 4;
let ghostImageLocations = [
    { x: 0, y: 0 },
    { x: 176, y: 0 },
    { x: 0, y: 121 },
    { x: 176, y: 121 },
];

// Game variables
let fps = 30;
let level = 1;
let pacman;
let bullet;
let levelselect;

levelselect = new Level(level);

let oneBlockSize = 20;
let score = 0;
let ghosts = [];
let wallSpaceWidth = oneBlockSize / 1.6;
let wallOffset = (oneBlockSize - wallSpaceWidth) / 2;
let wallInnerColor = "black";

let randomTargetsForGhosts = [
    { x: 1 * oneBlockSize, y: 1 * oneBlockSize },
    { x: 1 * oneBlockSize, y: (map.length - 2) * oneBlockSize },
    { x: (map[0].length - 2) * oneBlockSize, y: oneBlockSize },
    {
        x: (map[0].length - 2) * oneBlockSize,
        y: (map.length - 2) * oneBlockSize,
    },
];

// for (let i = 0; i < map.length; i++) {
//     for (let j = 0; j < map[0].length; j++) {
//         map[i][j] = 2;
//     }
// }

let createNewPacman = () => {
    pacman = new Pacman(
        oneBlockSize,
        oneBlockSize,
        oneBlockSize,
        oneBlockSize,
        oneBlockSize / 5
    );
};

let createBullet = (x, y) => {
    bullet = new Bullet(
        x,
        y,
        oneBlockSize,
        oneBlockSize,
        oneBlockSize / 5
    );
};

let gameLoop = (k) => {
    draw(k);
    update(k);
};

// let gameInterval = setInterval(gameLoop, 1000 / fps);

let restartPacmanAndGhosts = () => {
    createNewPacman();
    createGhosts();
};

let onGhostCollision = (k) => {
    if (lives > 0)
        lives--;
    console.log("lives=" + lives);
    if (lives <= 0) {
        drawGameOver(k);
        lives = 0;
        //if (!drawGameOver())
        //    window.close();
    } else {
        restartPacmanAndGhosts();
    }
};

let EliminateGhost = (ghost_index) => {
    // remove ghost
    // create new ghost
};

let checkGameClear = () => {
    let flag = 0;
    for (let i = 0; i < map.length; i++) {
        for (let j = 0; j < map[0].length; j++) {
            if (map[i][j] == 2) {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    return flag;
}

let isGameClear = 0;

let update = (k) => {
    pacman.moveProcess();
    pacman.eat();
    updateGhosts();
    // console.log("update function");
    if (pacman.checkGhostCollision(ghosts) || isGameOver == 1) {
        onGhostCollision(k);
    }
    if (!checkGameClear() && level <= 3) {
        isGameClear = 1;
        if (drawNextLevelGame(k, level+1)){
            level += 1;
        } else {
            window.close;
        }
    } else {
        isGameClear = 1;
    }
    //let ghost_index = -1;
    //ghost_index = bullet.checkGhostEliminated(ghosts)
    //if (ghost_index != -1) {
    //    EliminateGhost(ghost_index);
    //}
};

let drawFoods_and_item = (timeToGenerateItem) => {
    for (let i = 0; i < map.length; i++) {
        for (let j = 0; j < map[0].length; j++) {
            if (map[i][j] == 2) {
                createRect(
                    j * oneBlockSize + oneBlockSize / 3,
                    i * oneBlockSize + oneBlockSize / 3,
                    oneBlockSize / 3,
                    oneBlockSize / 3,
                    "#FEB897"
                );
            }
        }
    }
    if (timeToGenerateItem >= 2 && ((map[Math.floor(map[0].length / 2)][Math.floor(map.length / 2 - 1)] == 2))) {
        createCircle(
            Math.floor(map.length / 2 - 1) * oneBlockSize + oneBlockSize / 3,
            Math.floor(map[0].length / 2) * oneBlockSize + oneBlockSize / 3,
            oneBlockSize / 3,
            "#BEB897"
        );
    }
};

let drawLevelScreen = () => { 
    canvasContext.clearRect(0, 0, canvas.width, canvas.height);
    // draw "Pacman Game" at X = 10 and Y = 30   
    canvasContext.fillText("Level " + level, 150, oneBlockSize * (map.length / 2 + 1));
}

let drawNextLevelGame = (k, level) => {
    canvasContext.clearRect(0, 0, canvas.width, canvas.height);
    
    canvasContext.font = "20px Emulogic";    

    canvasContext.fillStyle = "white";
    // draw "Pacman Game" at X = 10 and Y = 30   
    canvasContext.fillText( "Game Clear", 110, oneBlockSize * (map.length / 2 + 1));

    canvasContext.fillText( "Score: " + score, 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize);

    canvasContext.fillText( "Press space to continue... Level " + level + " loading...", 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize * 2);

    if (k == 32) {
        restartPacmanAndGhosts();
        levelselect.levelMapSelect(level);
        // drawLevelScreen();
        return true;
    } else if (k == 78 || k == 110) {
        return false;
    } 
}

let isGameOver = 0;

let drawGameOver = (k) => {
    isGameOver = 1;
    
    canvasContext.clearRect(0, 0, canvas.width, canvas.height);
    
    canvasContext.font = "20px Emulogic";    

    canvasContext.fillStyle = "white";
    // draw "Pacman Game" at X = 10 and Y = 30   
    canvasContext.fillText( "Game Over", 110, oneBlockSize * (map.length / 2 + 1));
    canvasContext.fillText( "Play again?", 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize);
    canvasContext.fillText( "(Y/y) Yes", 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize * 2);
    canvasContext.fillText( "(N/n) No", 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize * 3);

    if (k == 89 || k == 121) {
        isGameOver = 0;
        enablegame = 1;
        level = 1;
        score = 0;
        lives = 5;
        restartPacmanAndGhosts();
        levelselect.levelMapSelect(level);
        /*
        for (let i = 0; i < map.length; i++) {
            for (let j = 0; j < map[0].length; j++) {
                map[i][j] = map_fixed[i][j];
            }
        }
        */
    } else if (k == 78 || k == 110) {
        window.close();
    } 
}

let drawingStartScreen = () => {
    // change font and font-size for better visibilty  

    canvasContext.font = "20px Emulogic";    

    canvasContext.fillStyle = "white";
    // draw "Pacman Game" at X = 10 and Y = 30   
    canvasContext.fillText( "=====  Pacman Game  =====", 110, oneBlockSize * (map.length / 2 + 1));
    canvasContext.fillText( "     Press J key to start game", 110, oneBlockSize * (map.length / 2 + 1) + oneBlockSize);
}

let drawRemainingLives = () => {
    canvasContext.font = "20px Emulogic";
    canvasContext.fillStyle = "white";
    canvasContext.fillText("Level: " + level, 110, oneBlockSize * (map.length + 1));
    canvasContext.fillText("Lives: ", 220, oneBlockSize * (map.length + 1));

    for (let i = 0; i < lives; i++) {
        canvasContext.drawImage(
            pacmanFrames,
            2 * oneBlockSize,
            0,
            oneBlockSize,
            oneBlockSize,
            350 + i * oneBlockSize,
            oneBlockSize * map.length + 2,
            oneBlockSize,
            oneBlockSize
        );
    }
};

let drawScore = () => {
    canvasContext.font = "20px Emulogic";
    canvasContext.fillStyle = "white";
    canvasContext.fillText(
        "Score: " + score,
        0,
        oneBlockSize * (map.length + 1)
    );
};

let draw = (k) => {
    console.log(k);
    if (k == 74 || k == 106 || k == 32)
        drawLevelScreen();
    else {
        current_time = new Date().getTime();
        t = Math.floor(((current_time - start_time) % (1000 * 60)) / 1000);
        // console.log("Elapsed seconds:" + t);
        canvasContext.clearRect(0, 0, canvas.width, canvas.height);
        createRect(0, 0, canvas.width, canvas.height, "black");
        drawWalls();
        drawFoods_and_item(t % 5);
        drawGhosts();
        pacman.draw();
        drawScore();
        drawRemainingLives();
    }
};

let drawStart = () => {
    drawingStartScreen();
}

let drawWalls = () => {
    for (let i = 0; i < map.length; i++) {
        for (let j = 0; j < map[0].length; j++) {
            if (map[i][j] == 1) {
                createRect(
                    j * oneBlockSize,
                    i * oneBlockSize,
                    oneBlockSize,
                    oneBlockSize,
                    "#342DCA"
                );
                if (j > 0 && map[i][j - 1] == 1) {
                    createRect(
                        j * oneBlockSize,
                        i * oneBlockSize + wallOffset,
                        wallSpaceWidth + wallOffset,
                        wallSpaceWidth,
                        wallInnerColor
                    );
                }

                if (j < map[0].length - 1 && map[i][j + 1] == 1) {
                    createRect(
                        j * oneBlockSize + wallOffset,
                        i * oneBlockSize + wallOffset,
                        wallSpaceWidth + wallOffset,
                        wallSpaceWidth,
                        wallInnerColor
                    );
                }

                if (i < map.length - 1 && map[i + 1][j] == 1) {
                    createRect(
                        j * oneBlockSize + wallOffset,
                        i * oneBlockSize + wallOffset,
                        wallSpaceWidth,
                        wallSpaceWidth + wallOffset,
                        wallInnerColor
                    );
                }

                if (i > 0 && map[i - 1][j] == 1) {
                    createRect(
                        j * oneBlockSize + wallOffset,
                        i * oneBlockSize,
                        wallSpaceWidth,
                        wallSpaceWidth + wallOffset,
                        wallInnerColor
                    );
                }
            }
        }
    }
};

let createGhosts = () => {
    ghosts = [];
    for (let i = 0; i < ghostCount * 2; i++) {
        let newGhost = new Ghost(
            9 * oneBlockSize + (i % 2 == 0 ? 0 : 1) * oneBlockSize,
            10 * oneBlockSize + (i % 2 == 0 ? 0 : 1) * oneBlockSize,
            oneBlockSize,
            oneBlockSize,
            pacman.speed / 2,
            ghostImageLocations[i % 4].x,
            ghostImageLocations[i % 4].y,
            124,
            116,
            6 + i
        );
        ghosts.push(newGhost);
    }
    // console.log(ghosts);
};

drawStart();
levelselect.levelMapSelect(level);

let enablegame = 0;
window.addEventListener("keydown", (event) => {
    let k = event.keyCode;

    setTimeout(() => {
        if ((k == 74 || k == 106) && enablegame == 0) {
            if (enablegame == 0) {    
                let gameInterval = setInterval(gameLoop, 1000 / fps);
            }
            createNewPacman();
            createGhosts();
            // drawLevelScreen();
            enablegame = 1;
        }
        if (enablegame == 1) {
            if (isGameOver == 1) {
                enablegame = 0;
                map[pacman.getMapX()][pacman.getMapY()] = 1;
                drawGameOver(k);
            } else {
                gameLoop(k);
                if (k == 37 || k == 65 && isGameOver == 0) {
                    // left arrow or a
                    pacman.nextDirection = DIRECTION_LEFT;
                    /*
                    if (bulletexist == 1) {
                        bullet.nextDirection = DIRECTION_LEFT;
                    }
                    */
                } else if (k == 38 || k == 87 && isGameOver == 0) {
                    // up arrow or w
                    pacman.nextDirection = DIRECTION_UP;
                    /*
                    if (bulletexist == 1) {
                        bullet.nextDirection = DIRECTION_UP;
                    }
                    */
                } else if (k == 39 || k == 68 && isGameOver == 0) {
                    // right arrow or d
                    pacman.nextDirection = DIRECTION_RIGHT;
                    /*
                    if (bulletexist == 1) {
                        bullet.nextDirection = DIRECTION_RIGHT;
                    }
                    */
                } else if (k == 40 || k == 83 && isGameOver == 0) {
                    // bottom arrow or s
                    pacman.nextDirection = DIRECTION_BOTTOM;
                    /*
                    if (bulletexist == 1) {
                        bullet.nextDirection = DIRECTION_BOTTOM;
                    }
                    */
                }
            }
        }
    }, 1);
});
