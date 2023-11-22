<?php get_header(); ?><!-- created on page 103 -->

					<section id="content" class="widecol alignleft">
					
						<!-- START WP_Query() Slider -->
						<div class="slider-wrapper theme-default">
              <div id="slider" class="nivoSlider">
                <a href="http://jesserfriedman.com" title="About Jesse Friedman">
                  <img width="530" height="267" class="attachment-slider wp-post-image" 
                    src="<?php echo get_template_directory_uri(); ?>/imgs/lg-slider.jpg" 
                    alt="About Jesse Friedman" 
                    title="About Jesse Friedman" />
                </a>
                <a href="http://worldclassdesigner.com" title="About Jeff Golenski">
                  <img width="530" height="267" class="attachment-slider wp-post-image" 
                    src="<?php echo get_template_directory_uri(); ?>/imgs/lg-slider.jpg" 
                    alt="About Jeff Golenski" 
                    title="About Jeff Golenski" />
                </a>
              </div>
							<?php /*<div id="slider" class="nivoSlider">
								<a href="" ><!-- get Custom Field page 205 -->
                  <img src="<?php echo get_template_directory_uri(); ?>/imgs/lg-slider.jpg" data-thumb="<?php echo get_template_directory_uri(); ?>/imgs/lg-slider.jpg" alt="" title=""  ><!-- modified on page 195 -->
                </a>
              </div><!-- slider -->
              */?>
						</div><!-- slider-wrapper -->
						<!-- END WP_Query() Slider -->
						
            <div id="posts">
            
              <h2 class="osc-cond txttranup">
                <?php echo get_the_category_by_id(get_option("default_category")); ?>
              </h2><!-- modified on page 106 -->
              
              <!-- START The Loop found on page 107 -->

              <?php if (have_posts()) : while (have_posts()) : the_post(); ?>
              <article class="post halfcol clear alignleft"><!-- Post Class page 248 --><!-- Loop structure built on pages 108-110 -->
                <?php the_post_thumbnail(); ?>
                <h3><a href="<?php the_permalink(); ?>" title="<?php the_title_attribute(); ?>"><?php the_title(); ?></a></h3><!-- modified on page 108-109 -->
                <p class="meta">
                  Posted <time datetime="<?php the_time('Y-m-d') ?>" pubdate="pubdate"><?php the_time('M n') ?></time> &#149; 
                  <?php comments_number("0 comments", "only 1 comment", "% comments"); ?>
                </p><!-- modified on page 109 -->
              </article>
              <?php endwhile; else: ?>
              <p><?php _e("Sorry, no posts matched your criteria."); ?></p>
              <?php endif; ?>
              <!-- END The Loop found on page 107 -->
            
            <div class="clear"></div>
            </div><!-- posts -->
						
						<!-- START Call to pagination function page 228 -->
						<nav id="pagination" class="clear">
							<ul class='page-numbers'>
								<li><span class='page-numbers current'>1</span></li>
								<li><a class='page-numbers' href='page/2/'>2</a></li>
								<li><a class='page-numbers' href='page/3/'>3</a></li>
								<li><a class="next page-numbers" href="page/2/">&gt;</a></li>
							</ul>
							<div class="clear"></div>
						</nav><!-- .pagination -->
						<!-- END Call to pagination function page 228 -->						
						
					</section>
						
					<!-- Start get_sidebar() -->	
					<?php get_sidebar(); ?> <!-- created on page 126 -->
					<!-- End get_sidebar() -->	
						
<?php get_footer(); ?><!-- created on page 113 -->