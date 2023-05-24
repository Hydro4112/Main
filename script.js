const dino = document.querySelector(".dino");
const obstacle = document.querySelector(".obstacle");
const scoreDisplay = document.querySelector(".score");
const highscoreDisplay = document.querySelector(".highscore");

let isJumping = false;
let isGameOver = false;
let speed = 1;
let score = 0;
let highscore = 0;
let scoreTimeout;

// Event listener für Tastendruck
document.addEventListener("keydown", (event) => {
  if (event.code === "Space" && !isJumping && !isGameOver) {
    jump();
  }
});

// Dino springen lassen
function jump() {
  isJumping = true;
  let start = null;

  function step(timestamp) {
    if (!start) start = timestamp;
    const progress = timestamp - start;

    if (progress < 150) {
      dino.style.bottom = 30 + (progress / 2.5) + "%";
    } else if (progress < 300) {
      dino.style.bottom = 90 - ((progress - 150) / 2.5) + "%";
    } else {
      dino.style.bottom = "30%";
      isJumping = false;
      return;
    }
    requestAnimationFrame(step);
  }

  requestAnimationFrame(step);
}

// Geschwindigkeit des Hindernisses aktualisieren
function updateObstacleSpeed() {
  obstacle.style.animationDuration = Math.max(1, 3 - speed) + "s";
}

// Hindernis-Animation anpassen
obstacle.addEventListener("animationiteration", () => {
  const randomHeight = 20 + Math.random() * 30;
  obstacle.style.height = randomHeight + "px";
  updateObstacleSpeed();
});

// Spiel zurücksetzen
function resetGame() {
  isGameOver = false;
  score = 0;
  speed = 1;
  updateObstacleSpeed();
  obstacle.style.animationPlayState = "running";
  gameLoop();
}

// Spiellogik
function gameLoop() {
  if (!isGameOver) {
    const dinoRect = dino.getBoundingClientRect();
    const obstacleRect = obstacle.getBoundingClientRect();

    if (
      dinoRect.left < obstacleRect.left + obstacleRect.width - 5 &&
      dinoRect.left + dinoRect.width - 5 > obstacleRect.left &&
      dinoRect.bottom < obstacleRect.bottom + obstacleRect.height - 5 &&
      dinoRect.bottom + dinoRect.height - 5 > obstacleRect.bottom
    ) {
      isGameOver = true;
      obstacle.style.animationPlayState = "paused";
      clearTimeout(scoreTimeout);
      if (score > highscore) {
        highscore = score;
        highscoreDisplay.textContent = "Highscore: " + highscore;
      }
      if (confirm("Game Over! Your score: " + score + ". Restart the game?")) {
        resetGame();
      }
    } else {
      scoreTimeout = setTimeout(() => {
        score++;
        scoreDisplay.textContent = "Score: " + score;
        if (score % 100 === 0) {
          speed += 0.1;
        }
        gameLoop();
      }, 1000);
    }
  }
}

gameLoop();