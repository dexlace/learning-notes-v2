const menuContainer = document.getElementById('menu-container');
const menu = document.getElementById('menu');
const rope = document.getElementById('rope');

let isMenuVisible = false;
let ropeTopPosition = 0;

rope.addEventListener('mousedown', (e) => {
  document.addEventListener('mousemove', onMouseMove);
  document.addEventListener('mouseup', onMouseUp);
});

function onMouseMove(e) {
  const newTopPosition = e.clientY;
  if (newTopPosition >= 0 && newTopPosition <= window.innerHeight) {
    ropeTopPosition = newTopPosition;
    rope.style.top = `${ropeTopPosition}px`;

    if (ropeTopPosition > 50) {
      menu.style.display = 'block';
      menuContainer.style.top = `${ropeTopPosition}px`;
      isMenuVisible = true;
    } else {
      menu.style.display = 'none';
      menuContainer.style.top = `0px`;
      isMenuVisible = false;
    }
  }
}

function onMouseUp() {
  document.removeEventListener('mousemove', onMouseMove);
  document.removeEventListener('mouseup', onMouseUp);

  if (isMenuVisible) {
    rope.style.top = `${menuContainer.offsetTop}px`;
  } else {
    rope.style.top = '0px';
  }
}
