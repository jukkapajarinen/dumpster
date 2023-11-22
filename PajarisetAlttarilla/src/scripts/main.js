import "bootstrap/js/dist/util";
import "bootstrap/js/dist/collapse";

/**************************************************/
/* Module variables */
/**************************************************/
let isMobile = $(window).width() <= 768;

/**************************************************/
/* General scroll handler */
/**************************************************/
let scrollHandler = e => {};

/**************************************************/
/* Smooth scrolling */
/**************************************************/
let smoothScroller = href => {
  if (href === "#" || href === "") {
    $("html, body").animate({ scrollTop: $("body").offset().top }, 500);
  } else {
    let anchorOffset = isMobile ? 492 : 91;
    $("html, body").animate({ scrollTop: $(href).offset().top - anchorOffset }, 500);
  }
}

/**************************************************/
/* Autoresizer */
/**************************************************/
let autoResize = e => {
  isMobile = $(window).width() <= 768
  $("html").css("font-size", isMobile ? "14px" : "18px");
};

/**************************************************/
/* Document ready handler */
/**************************************************/
let onReady = () => {

  // Autoresize call and bind autoreize handler
  autoResize();
  $(window).on("resize", e => autoResize(e));

  // Initially call and bind scrolling handler
  scrollHandler();
  $(window).on("scroll", e => scrollHandler(e));

  // Handlers for smooth scrolling to hash anchors
  if (window.location.hash.includes("#")) smoothScroller(window.location.hash);
  $(window).on('hashchange', e => { e.preventDefault(); smoothScroller(window.location.hash) });
  $(".back-to-top").on("click", e => { e.preventDefault(); smoothScroller("#") });
  $("a[href='#vihkiminen'], a[href='#haajuhla'], a[href='#majoitus'], a[href='#ilmoittautuminen'], a[href='#lisatietoja']")
    .on("click", e => {
    e.preventDefault();
    smoothScroller($(e.target).attr("href"))
  });
};

/**************************************************/
/* Initially call the onReady handler */
/**************************************************/
$(onReady);
