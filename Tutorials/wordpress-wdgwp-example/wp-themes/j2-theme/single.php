<?php get_header(); ?><!-- created on page 103 -->

					<section id="content" class="widecol alignleft">
					
						<!-- START The Loop page 132 -->
            <?php if (have_posts()) : while (have_posts()) : the_post(); ?>

            <?php the_post_thumbnail(); ?> 
						
						<article class="post"><!-- Post Class page 248 -->
						
							<header>
								<h1 class="text-shad-lt"> <?php the_title(); ?></h1><!-- modified page 133 -->
								<p class="meta">
                  Posted <time datetime="<?php the_time('Y-m-d') ?>" pubdate="pubdate"><?php the_time('M n') ?></time> &#149; 
                  <?php comments_number("0 comments", "only 1 comment", "% comments"); ?>
                </p><!-- modified page 133 -->
							</header>	
						
							<div class="content"><!-- modified page 135 -->
								<?php the_content(); ?>
							</div><!-- content -->
						
							<footer>
								<div class="tax clearfix">
									<div class="alignleft">
										<p>Filed Under: <?php the_category(', '); ?></p><!-- modified page 137 -->
									</div>
								</div>
                <?php if (get_the_tags()) { ?>
								<div class="alignright">
									<p>Tags: <?php the_tags(); ?></p>
								</div><!-- modified page 137 -->
                <? } ?>
							</footer>
							
							<nav id="pagi" class="clearfix">
								<ul>
                <?php previous_post_link("<li>%link</li>", "&lt; Previous Post"); ?>
                <?php next_post_link("<li>%link</li>", "&gt; Next Post"); ?>
								</ul>
							</nav><!-- .pagination -->
							
						</article>
						
						<!-- START Author section pages 139-141 -->
						<div class="author clearfix">
							<h3>Written by: <?php the_author_posts_link(); ?></h3>
							<?php echo get_avatar(
                get_the_author_meta("email"), '50', 'Mystery Man', 'Avatar of ' . get_the_author_meta("first_name") . ' ' . get_the_author_meta("last_name")
              ); ?>
              <?php if (get_the_author_meta("description")) { ?>
                <p><?php the_author_meta("description"); ?></p>
              <?php } ?>
              <?php if (get_the_author_meta("user_url")) { ?>
							  <a href="<?php the_author_meta("user_url"); ?>" title="<?php the_author_meta("first_name"); ?>'s Website'" target="_blank"><?php the_author_meta("user_url"); ?></a> 
              <?php } ?>
						</div><!-- author -->
						<!-- END Author section pages 139-141 -->
					
						<!-- START Author section pages 142 -->
						<div class="comments">
                <?php comments_template(); ?>
						</div><!-- comments-->
						<!-- END Author section pages 142 -->

            <?php endwhile; else: ?>
            <p><?php _e("Sorry, no posts matched your criteria."); ?></p>
            <?php endif; ?>
						<!-- END The Loop page 132 -->
						
					</section>
					
					<!-- Start get_sidebar() -->	
					<?php get_sidebar(); ?> <!-- created on page 126 -->
					<!-- End get_sidebar() -->	
						
<?php get_footer(); ?><!-- created on page 113 -->