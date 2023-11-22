<?php get_header(); ?><!-- created on page 103 -->

					<section id="content" class="widecol alignleft">

            <?php get_search_form(); ?>

						<h2 class="osc-cond txttranup"><?php _e("You are searching for \"" . get_search_query() . "\""); ?></h2><!-- modified on page 173 -->
						
            <div id="posts">
						
						<!-- START The Loop found on page 175 -->
            <?php if (have_posts()) : while (have_posts()) : the_post(); ?>
							<article class="post"><!-- Post Class page 248 -->
								<header>
                  <h3><a href="<?php the_permalink(); ?>" title="<?php the_title_attribute(); ?>"><?php the_title(); ?></a></h3><!-- modified on page 108-109 -->
                  <p class="meta">
                    Posted <time datetime="<?php the_time('Y-m-d') ?>" pubdate="pubdate"><?php the_time('M n') ?></time> &#149; 
                    <?php comments_number("0 comments", "only 1 comment", "% comments"); ?>
                  </p>
                </header>
								<p><?php the_excerpt(); ?></p>
							</article>
              <?php endwhile; else: ?>
              <p><?php _e("Sorry, your search for ". get_search_query() . " returned no results.."); ?></p>
              <?php endif; ?>
							<!-- END The Loop found on page 107 -->
							<div class="clear"></div>
						</div><!-- posts -->
						
						<nav id="pagination" class="clear">
							<ul class='page-numbers'>
								<li><span class='page-numbers current'>1</span></li>
								<li><a class='page-numbers' href='page/2/'>2</a></li>
								<li><a class='page-numbers' href='page/3/'>3</a></li>
								<li><a class="next page-numbers" href="page/2/">&gt;</a></li>
							</ul>
							<div class="clear"></div>
						</nav><!-- .pagination -->
						
					</section>
					
					<!-- Start get_sidebar() -->	
					<?php get_sidebar(); ?> <!-- created on page 126 -->
					<!-- End get_sidebar() -->	
						
<?php get_footer(); ?><!-- created on page 113 -->