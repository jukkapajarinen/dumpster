<?php get_header(); ?><!-- created on page 103 -->

					<section id="content" class="widecol alignleft">

						<div id="posts">

							<h2 class="osc-cond txttranup">
                <?php
                  if (is_day()) _e("You are viewing the " . get_the_date() . " daily archives");
                  elseif (is_month()) _e("You are viewing the " . get_the_date("F Y") . " monthly archives");
                  elseif (is_year()) _e("You are viewing the " . get_the_date("Y") . " yearly archives");
                  elseif (is_author()) _e("You are viewing the author archives");
                  else _e("You are viewing the " . single_cat_title("", false) . " archives");
                ?>
              </h2><!-- modified on page 168 -->

							<!-- START The Loop found on page 107 -->
              <?php if (have_posts()) : while (have_posts()) : the_post(); ?>

              <article class="halfcol clear alignleft">
                <?php the_post_thumbnail(); ?>
                <h3><a href="<?php the_permalink(); ?>" title="<?php the_title_attribute(); ?>"><?php the_title(); ?></a></h3><!-- modified on page 108-109 -->
                <p class="meta">
                  Posted <time datetime="<?php the_time('Y-m-d') ?>" pubdate="pubdate"><?php the_time('M n') ?></time> &#149; 
                  <?php comments_number("0 comments", "only 1 comment", "% comments"); ?>
                </p>
              </article>
							
              <?php endwhile; else: ?>
              <p><?php _e("The archives you're looking for could not be found."); ?></p>
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