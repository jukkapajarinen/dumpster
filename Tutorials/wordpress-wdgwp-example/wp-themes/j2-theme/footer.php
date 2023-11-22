</div><!-- widthfull mar0auto -->
			</div><!-- #container -->
			<section class="upper-footer clearfix">
				<div class="width100pad widthfull mar0auto">
					<!-- START dyanamic_sidebar() page 127 -->
          <?php get_sidebar("upper-footer"); ?>
					<!-- END dyanamic_sidebar() page 127 -->
				</div><!-- width100pad -->
			</section><!-- .upper-footer -->
						
			<footer class="main">
				<div class="width100pad clearfix widthfull mar0auto">
					<div class="widecol alignleft">
						
						<!-- START wp_nav_menu() function found on page 97 (classes may be different due to updates) -->
            <?php 
              $footer_nav = array(
                "theme_location" => "footer-nav",
                "container" => "nav",
                "container_class" => "menu-main-container",
                "container_id" => "footer-main",
                "depth" => 1
              );  
              wp_nav_menu($footer_nav); 
            ?>
						<!-- END wp_nav_menu() function found on page 97 -->
						
						<!-- START dyanamic_sidebar() page 127 -->
					  <?php get_sidebar("lt-footer"); ?>
						<!-- END dyanamic_sidebar() page 127 -->
					</div><!-- widecol -->	
						
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
						
						<!-- START dyanamic_sidebar() page 127 -->
					  <?php get_sidebar("rt-footer"); ?>
						<!--END dyanamic_sidebar() page 127 -->
						
					</div>
				</div><!-- width100pad -->
			</footer>
		</div><!-- width100pad -->
		<!-- wp_footer() page 84 -->
    <?php wp_footer(); ?>
	</body>
</html>