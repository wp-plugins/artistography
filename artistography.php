<?php
/*
 * Plugin Name: Artistography
 * Plugin URI: http://www.artistography.org/
 * Description: Build a collection of media from artists (videos, music, pictures) to organize a record label blog/website with a store connected to the music/songs or other types of art.
 * Version: 0.2.1
 * Author: MistahWrite
 * Author URI: http://www.LavaMonsters.com
 * Text Domain: artistography
 */
session_start();

define('WP_DEBUG', true); 
define('WP_DEBUG_LOG', true); 
define('WP_DEBUG_DISPLAY', true);

define('ARTISTOGRAPHY_VERSION', '0.2.1');

 // used to reference database tablenames in $TABLE_NAME, which is a globalized array
define('TABLE_ARTISTS', 0);
define('TABLE_ARTIST_ALBUM_LINKER', 1);
define('TABLE_ARTIST_FILE_DOWNLOAD', 2);
define('TABLE_ARTIST_MUSIC_ALBUMS', 3);
define('TABLE_ARTIST_IMAGE_GALLERY', 4);
define('TABLE_ARTIST_ORDERS', 5);

define('WP_ROOT', str_replace('/wp-admin', '', dirname($_SERVER['SCRIPT_FILENAME'])));
define('SITEURL', get_option('siteurl'));

define('ARTISTOGRAPHY_FILE_PATH', '/artistography'); //dirname(__FILE__));
define('ARTISTOGRAPHY_DIR_NAME', basename(ARTISTOGRAPHY_FILE_PATH));

define('CURRENCY', '$');

GLOBAL $i18n_domain; $i18n_domain = 'artistography'; // Localization/Internationalization

GLOBAL $artistography_plugin_dir; $artistography_plugin_dir = plugins_url('artistography', 'artistography');
GLOBAL $artistography_plugin_lang_dir; $artistography_plugin_lang_dir = basename(dirname(__FILE__));

GLOBAL $download_folder; $download_folder = '/downloads/';
GLOBAL $download_path; $download_path = WP_ROOT . $download_folder;
GLOBAL $explorer_path; $explorer_path = dirname(dirname($_SERVER['SCRIPT_FILENAME'])) . "/wp-content/plugins/artistography/downloads/index.php";

GLOBAL $download_icon_url; $download_icon_url = $artistography_plugin_dir . '/css/images/download.gif';
GLOBAL $download_icon_width; $download_icon_width = '150';
GLOBAL $download_icon_height; $download_icon_height = '127';

GLOBAL $add_to_cart_icon_url; $add_to_cart_icon_url = $artistography_plugin_dir . '/css/images/addtocartcc-orange.png';
GLOBAL $add_to_cart_icon_width; $add_to_cart_icon_width = '150';
GLOBAL $add_to_cart_icon_height; $add_to_cart_icon_height = '51';

GLOBAL $checkout_icon_url; $checkout_icon_url = $artistography_plugin_dir . '/css/images/yellow_checkout.png';
GLOBAL $checkout_icon_width; $checkout_icon_width = '150';
GLOBAL $checkout_icon_height; $checkout_icon_height = '50';

GLOBAL $buynow_icon_url; $buynow_icon_url = $artistography_plugin_dir . '/css/images/buynowcc-orange-2.png';
GLOBAL $buynow_icon_width; $buynow_icon_width = '213';
GLOBAL $buynow_icon_height; $buynow_icon_height = '95';

GLOBAL $TABLE_NAME; $TABLE_NAME =
  array ('artistography_artists',
         'artistography_artist_album_linker',
         'artistography_file_download',
         'artistography_music_albums',
         'artistography_image_gallery',
         'artistography_orders');

require_once('class/item.php.inc');
require_once('class/artist.php.inc');
require_once('class/music.php.inc');
require_once('class/discography.php.inc');
require_once('class/download.php.inc');
//require_once('class/image_gallery.php.inc');
require_once('class/orders.php.inc');
require_once('admin/general_funcs.php.inc');

function folder_is_empty($folder) {
  $counter = 0;
  if ($handle = opendir($dir)) {
     // This is the correct way to loop over the directory.
    while (false !== ($file = readdir($handle))) {
      if(!strcmp($file, ".") || !strcmp($file, "..")) continue;
      $counter++;
      closedir($handle);
      return false;
    }
    closedir($handle);
  }
  return true;
}

 // ACTIVATION FOR PLUGIN
function artistography_pluginInstall() {
  GLOBAL $wpdb, $TABLE_NAME, $download_path, $explorer_path, $download_folder, $i18n_domain;
 
  $version = get_option('wp_artistography_version', false);

   /*** Store any options ***/
  add_option('wp_artistography_donate_email', 'mistahwrite@gmail.com');
  add_option('wp_artistography_paypal_sandbox', true);
  add_option('wp_artistography_preserve_hidden_pages', true);
  add_option('wp_artistography_preserve_database', true);
  add_option('wp_artistography_email_notify_ftp', true);
  add_option('wp_artistography_ftp_host', '');
  add_option('wp_artistography_ftp_user', '');
  add_option('wp_artistography_ftp_pass', '');
  add_option('wp_artistography_ftp_path', '');
  add_option('wp_artistography_version', ARTISTOGRAPHY_VERSION, NULL, true);

   /* Create Download Page */
  if (!get_option('wp_artistography_download_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'Download',
       'post_name' => 'artistography_download',
       'post_content' => '[artistography_download]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_download_page', $my_post_id);
    }
  }
   /* Create Cart Page */
  if (!get_option('wp_artistography_cart_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'Cart',
       'post_name' => 'artistography_cart',
       'post_content' => '[artistography_show_cart]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_cart_page', $my_post_id);
    }
  }
   /* Create Checkout Page */
  if (!get_option('wp_artistography_checkout_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'Checkout',
       'post_name' => 'artistography_checkout',
       'post_content' => '[artistography_show_checkout]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_checkout_page', $my_post_id);
    }
  }

   /* Create Thank You Page */
  if (!get_option('wp_artistography_thankyou_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'Thank You',
       'post_name' => 'artistography_thankyou',
       'post_content' => '[artistography_show_thankyou]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_thankyou_page', $my_post_id);
    }
  }

   /* Create Orders Page */
  if (!get_option('wp_artistography_orders_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'Orders',
       'post_name' => 'artistography_orders',
       'post_content' => '[artistography_show_orders]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_orders_page', $my_post_id);
    }
  }

   /* Create IPN Page - PayPal Instant Notifications */
  if (!get_option('wp_artistography_ipn_page')) {
     // Create post object
    $my_post = array(
       'post_title' => 'IPN',
       'post_name' => 'artistography_ipn',
       'post_content' => '[artistography_ipn]',
       'comment_status' => 'closed',
       'ping_status' => 'closed',
       'post_status' => 'publish',
       'post_type' => 'page'
    );

     // Insert the post into the database
    $my_post_id = wp_insert_post( $my_post );
    if($my_post_id) {
      add_option('wp_artistography_ipn_page', $my_post_id);
    }
  }
 
  if (!is_dir($download_path)) {
    mkdir($download_path);
  }
  exec("cp $explorer_path $download_path/");

  if (version_compare($version, "0.1.1", '<')) {
     // this is an update to at least 0.1.1
    $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTISTS];
    $query = "ALTER TABLE $thetable DROP COLUMN myspace_url";
    $wpdb->query($query);

    $query = "ALTER TABLE $thetable DROP COLUMN birthday";
    $wpdb->query($query); 

    $query = "ALTER TABLE $thetable DROP COLUMN enabled";
    $wpdb->query($query);      

    $thetable = $wpdb->prefix . "artistography_track_list";
    $query = "DROP TABLE $thetable";
    $wpdb->query($query);
  }

  if (version_compare($version, "0.1.8", '<')) {
    $cart_page = get_option('wp_artistography_products_cart_page');
    if($cart_page) {
      $result = wp_delete_post($cart_page, true);
      if($result) {
        delete_option('wp_aristography_products_cart_page');
      }
    }

    $checkout_page = get_option('wp_artistography_products_checkout_page');
    if($checkout_page) {
      $result = wp_delete_post($checkout_page, true);
      if($result) {
        delete_option('wp_aristography_products_checkout_page');
      }
    }
  }

  if (version_compare($version, "0.1.9", '<')) {
    $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_MUSIC_ALBUMS];
    $query = "ALTER TABLE $thetable ADD COLUMN price DECIMAL (7,2) DEFAULT '0.00' NOT NULL";
    $wpdb->query($query);

    $query = "ALTER TABLE $thetable DELETE COLUMN free_download_enabled";
    $wpdb->query($query);

    $query = "ALTER TABLE $thetable DELETE COLUMN featured";
    $wpdb->query($query);

    $query = "ALTER TABLE $thetable DELETE COLUMN enabled";
    $wpdb->query($query);

    $query = "DROP TABLE wp_artistography_sales";
    $wpdb->query($query);

    $my_post = array(
      'ID'           => get_option('wp_artistography_download_page'),
      'comment_status' => 'closed',
      'ping_status' => 'closed'
    );
    wp_update_post( $my_post );

    $my_post = array(
      'ID'           => get_option('wp_artistography_cart_page'),
      'comment_status' => 'closed',
      'ping_status' => 'closed'
    );
    wp_update_post( $my_post );

    $my_post = array(
      'ID'           => get_option('wp_artistography_checkout_page'),
      'comment_status' => 'closed',
      'ping_status' => 'closed'
    );
    wp_update_post( $my_post );
  }

  if (version_compare($version, "0.2.1", '<')) {
    $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_ORDERS];
    $query = "ALTER TABLE $thetable ADD COLUMN user_id INT(10) UNSIGNED DEFAULT '0' NOT NULL";
    $wpdb->query($query);
  }

  update_option('wp_artistography_version', ARTISTOGRAPHY_VERSION);

    // Create Data Tables If They Don't Already Exist
  foreach ($TABLE_NAME as $key => $value) {
    $thetable = $wpdb->prefix . $value;

     // if tables don't already exist create them
    if($wpdb->get_var("show tables like '$thetable'") != $thetable) {
      $query = "CREATE TABLE $thetable (
                     id INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
                     create_date DATETIME NOT NULL,
                     update_date DATETIME NOT NULL,
                     poster_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     last_updated_by_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     ";
      switch ($key) {
        case TABLE_ARTISTS:
          $query .= "page_views INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     name TEXT NOT NULL,
                     picture_url TEXT NOT NULL,
                     url TEXT,
                     description LONGTEXT,
                     enabled BOOLEAN DEFAULT false NOT NULL,";
          break;

        case TABLE_ARTIST_ALBUM_LINKER:
          $query .= "artist_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     album_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,";
          break;

        case TABLE_ARTIST_FILE_DOWNLOAD:
          $query .= "file_name VARCHAR(250),
                     download_count INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     enabled BOOLEAN DEFAULT FALSE NOT NULL,";
          break;

        case TABLE_ARTIST_MUSIC_ALBUMS:
          $query .= "page_views INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     artist_id INT(10),
                     artist_name TEXT NOT NULL,
                     album_name TEXT NOT NULL,
                     album_date DATETIME NOT NULL,
                     artist_url TEXT,
                     picture_url TEXT NOT NULL,
                     store_url TEXT NOT NULL,
                     download_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     price DECIMAL (7,2) DEFAULT '0.00' NOT NULL,
                     description LONGTEXT,";
          break;

        case TABLE_ARTIST_IMAGE_GALLERY:
          $query .= "page_views INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     artist_id INT(10),
                     picture_url TEXT NOT NULL,
                     description LONGTEXT,
                     enabled BOOLEAN DEFAULT FALSE NOT NULL,";
          break;

	case TABLE_ARTIST_ORDERS:
	  $query .= "forename TEXT NOT NULL,
		     surname TEXT NOT NULL,
		     email TEXT NOT NULL,
		     address_line_1 TEXT NOT NULL,
                     postcode TEXT NOT NULL,
                     town TEXT NOT NULL,
                     itemsOrdered TEXT NOT NULL,
		     created DATETIME NOT NULL,
                     txn_id TEXT NOT NULL,
                     user_ip TEXT NOT NULL,
		     user_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,";
	  break;

      } // end switch($key)
      $query .= "\n  UNIQUE KEY id (id));";
      $wpdb->query($query);
    }
  } // end foreach
}
register_activation_hook( __FILE__, 'artistography_pluginInstall' );

 // DEACTIVATION FOR PLUGIN
function artistography_pluginUninstall() {
  GLOBAL $wpdb, $TABLE_NAME, $download_path, $i18n_domain;

  if (!strcmp(get_option('wp_artistography_preserve_hidden_pages'), NULL)) {
     /* Delete Download Page - So it isn't visible while Artistography is disabled */
    $download_page_id = get_option('wp_artistography_download_page');
    if ($download_page_id) {
       // force delete download page
      $result = wp_delete_post( $download_page_id, true ); 
      if(!$result) {
        delete_option('wp_artistography_download_page');
      }
    }

     /* Delete Cart Page - So it isn't visible while Artistography is disabled */
    $cart_page_id = get_option('wp_artistography_cart_page');
    if ($cart_page_id) {
       // force delete cart page
      $result = wp_delete_post( $cart_page_id, true );
      if(!$result) {
        delete_option('wp_artistography_cart_page');
      }
    }

     /* Delete Checkout Page - So it isn't visible while Artistography is disabled */
    $checkout_page_id = get_option('wp_artistography_checkout_page');
    if ($checkout_page_id) {
       // force delete checkout page
      $result = wp_delete_post( $checkout_page_id, true );
      if(!$result) {
        delete_option('wp_artistography_checkout_page');
      }
    }

     /* Delete Orders Page - So it isn't visible while Artistography is disabled */
    $orders_page_id = get_option('wp_artistography_orders_page');
    if ($orders_page_id) {
       // force delete checkout page
      $result = wp_delete_post( $orders_page_id, true );
      if(!$result) {
        delete_option('wp_artistography_orders_page');
      }
    }

     /* Delete Thank You Page - So it isn't visible while Artistography is disabled */
    $thankyou_page_id = get_option('wp_artistography_thankyou_page');
    if ($thankyou_page_id) {
       // force delete checkout page
      $result = wp_delete_post( $thankyou_page_id, true );
      if(!$result) {
        delete_option('wp_artistography_thankyou_page');
      }
    }

     /* Delete IPN Page - So it isn't visible while Artistography is disabled */
    $ipn_page_id = get_option('wp_artistography_ipn_page');
    if ($ipn_page_id) {
       // force delete checkout page
      $result = wp_delete_post( $ipn_page_id, true );
      if(!$result) {
        delete_option('wp_artistography_ipn_page');
      }
    }
  }

  if (!strcmp(get_option('wp_artistography_preserve_database'), NULL)) {
     //Delete any options that's stored
    delete_option('wp_artistography_donate_email');
    delete_option('wp_artistography_paypal_sandbox');
    delete_option('wp_artistography_preserve_hidden_pages');
    delete_option('wp_artistography_preserve_database');
    delete_option('wp_artistography_email_notify_ftp');
    delete_option('wp_artistography_ftp_host');
    delete_option('wp_artistography_ftp_user');
    delete_option('wp_artistography_ftp_pass');
    delete_option('wp_artistography_ftp_path');
    delete_option('wp_artistography_version');

    foreach ($TABLE_NAME as $key => $value) {
      $thetable = $wpdb->prefix . $value;
      $query = "DROP TABLE IF EXISTS $thetable";
      $wpdb->query($query);
    }
  }
}
register_deactivation_hook( __FILE__, 'artistography_pluginUninstall' );

function artistography_is_current_version() {
  $version = get_option('wp_artistography_version');
  return version_compare($version, ARTISTOGRAPHY_VERSION, '=') ? true : false;
}

function artistography_exclude_pages ($pages) {

	$excluded_ids =  array( get_option('wp_artistography_download_page'),
				get_option('wp_artistography_cart_page'),
				get_option('wp_artistography_checkout_page'),
				get_option('wp_artistography_thankyou_page'),
				get_option('wp_artistography_orders_page'),
				get_option('wp_artistography_ipn_page') );
	$shaved_pages = array();
	foreach($pages as $page) {
		if ( ! in_array($page->ID, $excluded_ids) ) {
			$shaved_pages[] = $page;
		}
	}
	return $shaved_pages;
}


function artistography_init() {
  GLOBAL $i18n_domain, $artistography_plugin_dir;

   /* Hide Pages from Menu */
  add_filter('get_pages', 'artistography_exclude_pages');

  if(!artistography_is_current_version()) artistography_pluginInstall();

  load_plugin_textdomain( $i18n_domain, false, $artistography_plugin_dir );
}
add_action('init', 'artistography_init');

  define(ADMIN_MENU_ORDERS, __('Orders', $i18n_domain));
  define(ADMIN_MENU_MANAGE_ARTISTS, __('Manage Artists', $i18n_domain));
  define(ADMIN_MENU_MANAGE_MUSIC, __('Music Albums', $i18n_domain));
  define(ADMIN_MENU_MANAGE_DOWNLOADS, __('Downloads', $i18n_domain));
  define(ADMIN_MENU_MANAGE_DISCOGRAPHY, __('Discography', $i18n_domain));
//  define(ADMIN_MENU_MANAGE_GALLERIES, __('Galleries', $i18n_domain));
//  define(ADMIN_MENU_MANAGE_ALBUM_ART, __('Album Art', $i18n_domain));
  define(ADMIN_MENU_FTP_UPLOADER, __('FTP Uploader', $i18n_domain));
  define(ADMIN_MENU_OPTIONS, __('Options', $i18n_domain));
  define(ADMIN_MENU_ABOUT, __('About', $i18n_domain));

  define(TOP_LEVEL_HANDLE, 'artistography-top-level');
  define(SUBMENU_MANAGE_ARTISTS_HANDLE, 'artistography-submenu-manage-artists');
  define(SUBMENU_MANAGE_MUSIC_HANDLE, 'artistography-submenu-manage-music');
  define(SUBMENU_MANAGE_DOWNLOADS_HANDLE, 'artistography-submenu-manage-downloads');
  define(SUBMENU_MANAGE_DISCOGRAPHY_HANDLE, 'artistography-submenu-manage-discography');
//  define(SUBMENU_MANAGE_GALLERIES_HANDLE, 'artistography-submenu-manage-galleries');
  define(SUBMENU_FTP_UPLOADER, 'artistography-submenu-ftp-uploader');
  define(SUBMENU_OPTIONS_HANDLE, 'artistography-submenu-options');
  define(SUBMENU_ABOUT_HANDLE, 'artistography-submenu-about');

function artistography_enqueue_admin_style_and_scripts() {
    GLOBAL $artistography_plugin_dir;

    wp_enqueue_style( 'jquery-ui', $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.css', array(), '1.11.2', 'all');
    wp_enqueue_style( 'jquery-ui', $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.theme.css', array(), '1.11.2', 'all');
    wp_enqueue_script( 'jquery-ui',  $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.js', array( 'jquery' ), '1.0.0');

    wp_enqueue_style( 'artistography', $artistography_plugin_dir . '/css/admin-style.css', array(), ARTISTOGRAPHY_VERSION, 'all');
    wp_enqueue_script( 'artistography',  $artistography_plugin_dir . '/js/admin.js', array( 'jquery-ui' ), ARTISTOGRAPHY_VERSION);
}

function artistography_enqueue_style_and_scripts() {
    GLOBAL $artistography_plugin_dir;

    wp_enqueue_style( 'jquery-ui', $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.css', array(), '1.11.2', 'all');
    wp_enqueue_style( 'jquery-ui', $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.theme.css', array(), '1.11.2', 'all');
    wp_enqueue_script( 'jquery-ui',  $artistography_plugin_dir . '/js/jquery-ui-1.11.2/jquery-ui.js', array( 'jquery' ), '1.0.0');

    wp_enqueue_style( 'artistography', $artistography_plugin_dir . '/css/style.css', array(), ARTISTOGRAPHY_VERSION, 'all');
    wp_enqueue_script( 'artistography',  $artistography_plugin_dir . '/js/script.js', array( 'jquery-ui' ), ARTISTOGRAPHY_VERSION);
}

 /* START ADMIN MENU INTERFACE */
add_action('admin_menu', 'artistography_plugin_menu');
function artistography_plugin_menu() {

  GLOBAL $artistography_plugin_dir, $i18n_domain;

  if( FALSE !== stripos($_GET['page'], 'artistography') ) {
    artistography_enqueue_admin_style_and_scripts();
  }

  add_menu_page(ADMIN_MENU_STATS, __('Artistography', $i18n_domain), 'manage_options', TOP_LEVEL_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_ORDERS), ADMIN_MENU_ORDERS, 'manage_options', TOP_LEVEL_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ARTISTS), ADMIN_MENU_MANAGE_ARTISTS, 'manage_options', SUBMENU_MANAGE_ARTISTS_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_MUSIC), ADMIN_MENU_MANAGE_MUSIC, 'manage_options', SUBMENU_MANAGE_MUSIC_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_DISCOGRAPHY), ADMIN_MENU_MANAGE_DISCOGRAPHY, 'manage_options', SUBMENU_MANAGE_DISCOGRAPHY_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_DOWNLOADS), ADMIN_MENU_MANAGE_DOWNLOADS, 'manage_options', SUBMENU_MANAGE_DOWNLOADS_HANDLE, 'artistography_plugin_options');
//  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_GALLERIES), ADMIN_MENU_MANAGE_GALLERIES, 'manage_options', SUBMENU_MANAGE_GALLERIES_HANDLE, 'artistography_plugin_options');
//  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ALBUM_ART), ADMIN_MENU_MANAGE_ALBUM_ART, 'manage_options', SUBMENU_MANAGE_ALBUM_ART_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_FTP_UPLOADER), ADMIN_MENU_FTP_UPLOADER, 'manage_options', SUBMENU_FTP_UPLOADER, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_OPTIONS), ADMIN_MENU_OPTIONS, 'manage_options', SUBMENU_OPTIONS_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_ABOUT), ADMIN_MENU_ABOUT, 'manage_options', SUBMENU_ABOUT_HANDLE, 'artistography_plugin_options');

}

function artistography_plugin_options() {
  GLOBAL $wpdb, $i18n_domain, $title, $TABLE_NAME, $download_folder, $download_path, $explorer_path, $artistography_plugin_dir;

  if (!current_user_can('manage_options'))  {
    wp_die( __('You do not have sufficient permissions to access this page.', $i18n_domain) );
  }

  echo "<div class='wrap'>\n";
  echo "<h2>$title</h2>\n";
  switch($title) {
    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_OPTIONS):
      require_once('admin/options.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_ORDERS):
      require_once('admin/orders.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ARTISTS):
      require_once('admin/manage_artists.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_MUSIC):
      require_once('admin/manage_music.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_DOWNLOADS):
      require_once('admin/download_insert.php.inc');
      require_once('admin/download_stats.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_DISCOGRAPHY):
      require_once('admin/manage_discography.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_GALLERIES):
      require_once('admin/manage_galleries.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ALBUM_ART):
      require_once('admin/manage_album_art.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_FTP_UPLOADER):
      require_once('admin/ftp_uploader.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_ABOUT):    default:
      require_once('admin/about.php.inc');
      break;
  }
  echo '</div>';
}
 /* END ADMIN MENU INTERFACE */

?>
