<?php
/*
Template Name: Full Width
*/ 
?><!-- created on page 160 -->

			<?php get_header(); ?><!-- created on page 103 -->

      <section id="content" class="width100 alignleft">	

        <?php if (have_posts()) : while (have_posts()) : the_post(); ?>

        <?php the_post_thumbnail(); ?> 

        <nav class="breadcrumb">
          <!-- Breadcrumb NavXT 4.1.0 -->
          <p><?php if (function_exists("bcn_display")) bcn_display(); ?></p>
        </nav>

        <article class="page"><!-- Post Class page 248 -->

          <header>
            <h1 class="text-shad-lt"><?php the_title(); ?></h1><!-- modified on page 157 -->
          </header>				
          
          <?php if (get_the_excerpt()) { ?>
            <h2 class="tagline"><?php echo get_the_excerpt(); ?><!-- The EXCERPT --></h2><!-- modified on page 158 -->
          <?php } ?>
              
          <div class="content"><!-- modified on page 159 -->
            <?php the_content(); ?>
          </div><!-- content -->
          
        </article>
        <div class="comments">
          <p class="nocomments">Comments are closed.</p>
        </div><!-- comments-->

        <?php endwhile; else: ?>
        <p><?php _e("Sorry, no page matched your criteria."); ?></p>
        <?php endif; ?>
        <!-- END The Loop page 152 -->

      </section>
					
<?php get_footer(); ?><!-- created on page 113 -->