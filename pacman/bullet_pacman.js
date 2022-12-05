class Bullet {
    constructor(x, y, width, height, speed) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.speed = speed;
        this.direction = 4;
        this.nextDirection = 4;
        this.frameCount = 7;
        this.currentFrame = 1;
        this.ratio = 10;
        setInterval(() => {
            this.changeAnimation();
        }, 100);
    }

    changeAnimation() {
        this.currentFrame =
            this.currentFrame == this.frameCount ? 1 : this.currentFrame + 1;
    }

    moveForwards() {
        console.log("current direction:" + pacman.direction);

        switch (pacman.direction) {
            case DIRECTION_RIGHT: // Right
                this.x += this.ratio * this.speed;
                break;
            case DIRECTION_UP: // Up
                this.y -= this.ratio * this.speed;
                break;
            case DIRECTION_LEFT: // Left
                this.x -= this.ratio * this.speed;
                break;
            case DIRECTION_BOTTOM: // Bottom
                this.y += this.ratio * this.speed;
                break;
        }

        console.log("pacman.x:" + pacman.x);
        console.log("pacman.y:" + pacman.y);
        console.log("this.x:" + this.x);
        console.log("this.y:" + this.y);
    }

    draw(bulletexist) {
        if (bulletexist === 1) {
            console.log("bullet exits...");
            canvasContext.save();
            canvasContext.translate(
                this.x + oneBlockSize / 2,
                this.y + oneBlockSize / 2
            );
            canvasContext.rotate((this.direction * 90 * Math.PI) / 180);
            canvasContext.translate(
                -this.x - oneBlockSize / 2,
                -this.y - oneBlockSize / 2
            );
            canvasContext.drawImage(
                bulletFrames,
                (this.currentFrame - 1) * oneBlockSize,
                0,
                oneBlockSize,
                oneBlockSize,
                this.x,
                this.y,
                this.width,
                this.height
            );
            canvasContext.restore();
        }
    }

    checkGhostEliminated(ghosts) {
        let index = -1;
        for (let i = 0; i < ghosts.length; i++) {
            let ghost = ghosts[i];
            if (
                ghost.getMapX() == this.x &&
                ghost.getMapY() == this.y
            ) {
                return i;
            }
        }
        return index;
    }

    checkCollisions() {
        let isCollided = false;
        if (
            map[parseInt(this.y / oneBlockSize)][
                parseInt(this.x / oneBlockSize)
            ] == 1 ||
            map[parseInt(this.y / oneBlockSize + 0.9999)][
                parseInt(this.x / oneBlockSize)
            ] == 1 ||
            map[parseInt(this.y / oneBlockSize)][
                parseInt(this.x / oneBlockSize + 0.9999)
            ] == 1 ||
            map[parseInt(this.y / oneBlockSize + 0.9999)][
                parseInt(this.x / oneBlockSize + 0.9999)
            ] == 1
        ) {
            isCollided = true;
        }
        return isCollided;
    }
}