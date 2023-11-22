import 'jquery-aniview';
import Particles from 'particlesjs/dist/particles';

/**************************************************/
/* Module variables */
/**************************************************/
let isMobile = $(window).width() <= 768;

/**************************************************/
/* Mailto spambot prevention */
/**************************************************/
let createAddress = i => {
  let part1 = "tcatnoc".split("").reverse().join("");
  let part2 = Math.pow(2,6);
  let part3 = String.fromCharCode(part2);
  let part4 = "moc.nenirajapakkuj".split("").reverse().join("");
  return part1 + part3 + part4;
}

let createMailtoAnchor = i => {
  return `<a href="${"mai"+"lto"+":"+createAddress(i)}">${createAddress(i)}</a>`;
}

/**************************************************/
/* Document ready handler */
/**************************************************/
let onReady = () => {

  // Set the base font-size for mobile
  if (isMobile) {
    $("html").css("font-size", "14px");
  }

  // Add Aniview to hero sections
  $('.aniview').AniView({animateThreshold: 100, scrollPollInterval: 50});

  // Add Particles background
  Particles.init({
    selector: '#particlesjs-canvas',
    maxParticles: 60,
    sizeVariations: 3,
    color: "#ffffff",
    connectParticles: true
  });

  // Eventlistener for bavbar toggle
  $(".navbar-burger").on('click', (e) => {
    $(".navbar-burger").toggleClass("is-active");
    $(".navbar-menu").toggleClass("is-active");
  });

  // Add mailto anchors to prevent spambots
  $("#address1").html(createMailtoAnchor(1));
}

/**************************************************/
/* Initially call the onReady handler */
/**************************************************/
$(onReady);
