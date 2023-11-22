<?php

function j2theme_filter_wp_title($currentTitle, $sep, $sepLocal) {
  $site_name = get_bloginfo("name");
  $full_title = $site_name . $currentTitle;

  if (is_front_page() || is_home()){
    $site_desc = get_bloginfo("description");
    $full_title .= " " . $sep . " " . $site_desc;
  }

  return $full_title;
}

add_filter("wp_title", "j2theme_filter_wp_title", 10, 3);

/* Register Menus on page 90 */
register_nav_menus(
  array(
    "main-nav-header-top" => "Main Nav, Top of Header",
    "sub-nav-header-bottom" => "Sub Nav, Bottom of Header",
    "footer-nav" => "Footer Menu"
  )
);

add_theme_support("post-thumbnails");


/* Register Sidebars on page 119 */
$j2theme_header_sidebar = array(
  "name" => "Header",
  "id" => "header",
  "description" => "Widgets placed here will display in the header to the right of the logo",
  "before_widget" => "",
  "after_widget" => "",
  "before_title" => "<h2>",
  "after_title" => "</h2>"
);
register_sidebar($j2theme_header_sidebar);
$j2theme_aside_sidebar = array(
  "name" => "Aside",
  "id" => "aside",
  "description" => "Widgets placed here will go in the Right hand sidebar",
  "before_widget" => '<div class="widget">',
  "after_widget" => "</div><!-- class: widget -->",
  "before_title" => '<h3 class="widgettitle">',
  "after_title" => "</h3>"
);
register_sidebar($j2theme_aside_sidebar);
$j2theme_upperfooter_sidebar = array(
  "name" => "Upper footer",
  "id" => "upper-footer",
  "description" => "Widgets placed here will go in the upper footer area",
  "before_widget" => '<div class="widget thirdcol alignleft">',
  "after_widget" => "</div><!-- class: widget -->",
  "before_title" => '<h3 class="widgettitle">',
  "after_title" => "</h3>"
);
register_sidebar($j2theme_upperfooter_sidebar);
$j2theme_footer_lt_sidebar = array(
  "name" => "Left footer",
  "id" => "left-footer",
  "description" => "Widgets placed here will display in the left column of the footer",
  "before_widget" => "",
  "after_widget" => "",
  "before_title" => '<h3 class="widgettitle">',
  "after_title" => "</h3>"
);
register_sidebar($j2theme_footer_lt_sidebar);
$j2theme_footer_rt_sidebar = array(
  "name" => "Right footer",
  "id" => "right-footer",
  "description" => "Widgets placed here will display in the right column of the footer",
  "before_widget" => "",
  "after_widget" => "",
  "before_title" => '<h3 class="widgettitle">',
  "after_title" => "</h3>"
);
register_sidebar($j2theme_footer_rt_sidebar);

/* Register Sidebar on page 181 */
$j2theme_404_sidebar = array(
  "name" => "404 Error Page",
  "id" => "fourohfour",
  "description" => "Widgets placed here will go on the 404 error page template",
  "before_widget" => '<div class="widget">',
  "after_widget" => "</div>",
  "before_title" => '<h3 class="widgettitle">',
  "after_title" => "</h3>"
);
register_sidebar($j2theme_404_sidebar);


/* Post Type Support for Tagline found on page 158 */
add_post_type_support("page", "excerpt");



/* Register Post Thumbnails on page 192 */




/* Custom Pagination function page 227 */




/* Custom Header and Background support page 249 */