<!DOCTYPE html>
<html <?php language_attributes(); ?>><!-- modified on page 76 -->
	<head>
		<title><?php wp_title("|"); ?></title><!-- modified on page 77 -->
	    <meta http-equiv="Content-Type" content="<?php bloginfo("html_type"); ?>" charset="<?php bloginfo("charset"); ?>"><!-- modified on page 80 -->
	    <meta name="viewport" content="width=device-width" />
	    <!-- custom web fonts -->
	    	<link href='http://fonts.googleapis.com/css?family=Open+Sans+Condensed:700' rel='stylesheet' type='text/css'>
	    	<link href='http://fonts.googleapis.com/css?family=Open+Sans:600italic,600' rel='stylesheet' type='text/css'>
	    <!-- custom web fonts -->
	    <!-- Dear Reader,
	    Just a quick note to make something clear. The css here is not going to be perfect or browser compatible. In the future this theme will be available in the the Theme Directory for all to download and at that point the css will be altered to provide the best possible user experience for everyone. However the css included in with these files is optimized for the latest Firefox and Chrome browsers only. REMEMBER the goal of these files is to help you learn how to convert and build WordPress Templates not necessarily write great HTML or CSS. In other words, ignore any css bugs cause they aren't important, happy coding :) -->
	    <link rel="stylesheet" type="text/css" media="all" href="<?php bloginfo("stylesheet_url"); ?>" /><!-- modified on page 81 -->
	    <link rel="apple-touch-icon" href="<?php echo get_template_directory_uri(); ?>/images/apple-icon-file.png"><!-- This needs to be linked to the same way you'll link to js and other theme files found on page 82 -->
		<link rel="icon" type="image/x-icon" href="<?php echo get_template_directory_uri(); ?>/images/favicon.ico" /><!-- These need to be linked to the same way you'll link to js and other theme files found on page 82 -->
		<script type='text/javascript' src='<?php echo get_template_directory_uri(); ?>/scripts/jquery.js'></script><!-- jQuery should be enqueued via wp_enqueue_script() http://wdgwp.com/enqueue or page 242 we didn't cover this in detail in the book. When you enqueue your script it should go above the wp_head() function (because it uses that to embed the script) then both the enqueue function and wp_head() should be above any other calls that require jQuery otherwise they won't exist before you embed them. -->
		<!-- wp_head() goes here if you're enqueueing page 82-->
    <?php wp_head(); ?>
    <!-- HTML 5 Shiv for IE -->
    <script type="text/javascript" src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
    <!-- HTML 5 Shiv -->
    <!-- JavaScripts -->
    <script src="<?php echo get_template_directory_uri(); ?>/scripts/selectnav.js"></script>
    <script src="<?php echo get_template_directory_uri(); ?>/scripts/functions.js" type="text/javascript"></script>
    <!-- Nivo Slider -->
    <script src="<?php echo get_template_directory_uri(); ?>/scripts/jquery.nivo.slider.js" type="text/javascript"></script><!-- modified on page 82 -->
    <link rel="stylesheet" type="text/css" href="<?php echo get_template_directory_uri(); ?>/css/nivo/nivo-slider.css" ><!-- modified on page 81 -->
    <link rel="stylesheet" type="text/css" href="<?php echo get_template_directory_uri(); ?>/css/nivo/nivo.css" ><!-- modified on page 81 -->
    <!-- Nivo Slider -->
    <!-- JavaScripts -->
	</head>
	
	<body <?php body_class("container"); ?>><!-- insert body class page 83 some things will look broken until this is put in -->
		<div class="width100">
			<header id="header" class="width100 clearfix">
				<div class="navbar width100pad clearfix">
					<div class="widthfull mar0auto">
          
						<!-- START wp_nav_menu() function found on page 95 -->
            <?php 
              $main_menu_header_top = array(
                "theme_location" => "main-nav-header-top",
                "container" => "nav",
                "container_class" => "alignleft widecol",
                "container_id" => "header-main-nav",
                "depth" => 1
              );  
              wp_nav_menu($main_menu_header_top); 
            ?>
						<!-- END wp_nav_menu() function found on page 95 -->

						<div class="narcolrt alignright">
							<nav class="alignright social">
								<ul>
									<li class="alignleft nobull"><a href="http://twitter.com/professor" target="_blank"><img src="<?php echo get_template_directory_uri(); ?>/images/social/twitter-lg.png" alt="Twitter Icon" title="J2 Design on Twitter"></a></li>
									<li class="alignleft nobull"><a href="https://www.facebook.com/wordpressandweb" target="_blank"><img src="<?php echo get_template_directory_uri(); ?>/images/social/facebook-lg.png" alt="Facebook Icon" title="J2 Design on Facebook"></a></li>					
									<li class="alignleft nobull"><a href="feed/" target="_blank"><img src="<?php echo get_template_directory_uri(); ?>/images/social/rss-lg.png" alt="J2 Design RSS Icon" title="Subscribe to J2 Design"></a></li>
								</ul>
							</nav><!-- .social -->
							<form class="alignright">
								<input id="s" name="s" type="text" value="search" class="osc italic txttranup">
								<input id="submit" name="submit" type="submit" value="" class="alignleft">
							</form><!-- form (search box) -->
						</div><!-- .narcolrt -->
					</div><!-- .widthfull -->
				</div><!-- .navbar -->
				<div class="width100pad clear widthfull mar0auto">
					<div class="halfcol alignleft">
						<h1 class="displaynone">Your Business Name</h1>
						<a href="/" title=""><img src="<?php echo get_template_directory_uri(); ?>/imgs/logo.png" alt="" class="logo" /></a>
					</div><!-- .halfcol -->

					<!-- START dyanamic_sidebar() page 127 -->
					<?php get_sidebar("header"); ?>
					<!-- END dyanamic_sidebar() page 127 -->

				</div><!-- width100pad -->
			</header><!-- header -->
						
			<!-- START wp_nav_menu() function found on page 96 -->
      <?php 
        $sub_menu_header_bottom = array(
          "theme_location" => "sub-nav-header-bottom",
          "container" => "nav",
          "container_class" => "clearfix subnav",
          "menu_class" => "width100pad widthfull mar0auto",
          "depth" => 1
        );  
        wp_nav_menu($sub_menu_header_bottom); 
      ?>
			<!-- END wp_nav_menu() function found on page 96 -->
						
			<div id="container" class="width100pad clearfix">
				<div class="widthfull mar0auto">
