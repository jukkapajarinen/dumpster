jQuery(document).ready(function($) { /* For more info on why this looks this way go to http://wdgwp.com/jquery_noconflict */
	
	/* Nivo Slider for the Homepage */
    if( $('#slider').length ) {
    	$('#slider').nivoSlider();
    }
    
    /* Some removing of attributes for responsive integrity */
    $('.tagcloud a').removeAttr('style');
    $('.attachment-post-thumb').removeAttr('width').removeAttr('height');
    $('.attachment-post-thumb').width('100%');
    $('.attachment-page-featured-image').removeAttr('width').removeAttr('height');
    $('.wp-caption').removeAttr('width').removeAttr('height');
    $('.attachment-page-featured-image').width('100%');
    
    /* Converts traditional nav to dropdown on mobile devices */
	selectnav('main-nav-header-top');
	selectnav('sub-nav-header-bottom');
	selectnav('footer-nav');
	
	
});