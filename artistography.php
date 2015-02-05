<?php
/*
 * Plugin Name: Artistography
 * Plugin URI: http://www.artistography.org/
 * Description: Build a collection of media from artists (videos, music, pictures) to organize a record label blog/website with a store connected to the music/songs or other types of art.
 * Version: 0.0.4-alpha
 * Author: MistahWrite
 * Author URI: http://www.LavaMonsters.com
 * Text Domain: artistography
 */
define('WP_DEBUG', true); 
define('WP_DEBUG_LOG', true); 
define('WP_DEBUG_DISPLAY', true);

define('ARTISTOGRAPHY_VERSION', '0.0.4-alpha');
 // whether to preserve database on plugin deactivation
define('PRESERVE_DATABASE_TABLES', true);  // TODO: make this user configurable for later

 // used to reference database tablenames in $TABLE_NAME, which is a globalized array
define('TABLE_ARTISTS', 0);
define('TABLE_ARTIST_ALBUM_LINKER', 1);
define('TABLE_ARTIST_FILE_DOWNLOAD', 2);
define('TABLE_ARTIST_TRACK_LIST', 3);
define('TABLE_ARTIST_MUSIC_ALBUMS', 4);
define('TABLE_ARTIST_IMAGE_GALLERY', 5);

define('WP_ROOT', str_replace('/wp-admin', '', dirname($_SERVER['SCRIPT_FILENAME'])));

define('ARTISTOGRAPHY_FILE_PATH', dirname(__FILE__));
define('ARTISTOGRAPHY_DIR_NAME', basename(ARTISTOGRAPHY_FILE_PATH));

GLOBAL $i18n_domain; $i18n_domain = 'artistography'; // Localization/Internationalization
GLOBAL $download_folder; $download_folder = '/downloads/';
GLOBAL $download_path; $download_path = WP_ROOT . $download_folder;

GLOBAL $ftpuploader_folder; $ftpuploader_folder = '/ftpuploader/';
GLOBAL $ftpuploader_path; $ftpuploader_path = WP_ROOT . $ftpuploader_folder;

GLOBAL $artistography_plugin_dir; $artistography_plugin_dir = __FILE__;
GLOBAL $artistography_plugin_lang_dir; $artistography_plugin_lang_dir = basename(dirname(__FILE__));
GLOBAL $TABLE_NAME; $TABLE_NAME =
  array ('artistography_artists',
         'artistography_artist_album_linker',
         'artistography_file_download',
         'artistography_track_list',
         'artistography_music_albums',
         'artistography_image_gallery');

require_once('class/item.php.inc');
require_once('class/artist.php.inc');
require_once('class/music.php.inc');
require_once('class/track_list.php.inc');
require_once('class/discography.php.inc');
//require_once('class/image_gallery.php.inc');
require_once('admin/general_funcs.php.inc');

 /* Process Download request */
add_action('parse_request', 'my_custom_url_handler');
function my_custom_url_handler() {

   global $wpdb, $i18n_domain, $TABLE_NAME;

   $uri = explode('/', $_SERVER["REQUEST_URI"]);
   $this_id = 0; $val = 0;
   foreach ($uri as $key => $value) {
     if ($value === 'artistography-download' or $value === 'download') {
       $this_id = $key + 1;
       $val = $uri[$this_id];
       break;
     }
   }
   unset($value);

   if( $this_id != 0 ) {
      $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_FILE_DOWNLOAD];
      $query = $wpdb->prepare("SELECT *
                                 FROM $thetable
                                WHERE id = %u", $val);
      $the_row = $wpdb->get_row($query);
      $num_rows = $wpdb->num_rows;
      $loc = get_option('siteurl') . "/downloads/" . $the_row->file_name;

//      header("Location: " .$loc, true, 303);
      get_header();

       //increase counter
      $query = $wpdb->prepare("UPDATE $thetable
                                  SET download_count=download_count+1
                               WHERE id = %u", $val);
      $wpdb->query($query);

?>
<div class="mainbar">
    <div class="mainbar_top">
        <div class="mainbar_bottom">
            <div class="mainbar_inner">                
                <div class="post firstpost">
                    <div class="post_date">
                        <div class="post_date_top"><? echo date('d'); ?></div>
                        <div class="post_date_bottom"><? echo date('M'); ?></div>                                            
                    </div>
                    <h2 class="post_header" id="post-x"><a href="" rel="bookmark" title="<? printf(__("Permanent Link to Download ID %s", $i18n_domain), $this_id); ?>"><? _e("Download", $i18n_domain); ?></a></h2>
                    <div class="post_line"></div>
                    <div class="post_content">
<? if ($num_rows > 0) { ?>
                      <meta http-equiv="refresh" content="2;url=<? echo $loc; ?>">
                      <? _e("If your download does not begin in about 2-5 seconds, please click here", $i18n_domain); ?>: <a href='<? echo $loc; ?>'><? echo $loc; ?></a>.<br/><br/>

printf(__("This has been downloaded <i><b>%s</b></i> times.", $i18n_domain), $the_row->download_count); ?><br/><br/>

<? _e("We appreciate your interest, and hope that you will consider at least a $1.00 donation by clicking the link below.  Feel free to tell us why you're donating to us as it means a lot.  Many thanks from the crew!", $i18n_domain); ?><br/><br/>

<center>
<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
<input type="hidden" name="cmd" value="_donations">
<input type="hidden" name="business" value="skimpkillah@gmail.com">
<input type="hidden" name="lc" value="US">
<input type="hidden" name="no_note" value="0">
<input type="hidden" name="currency_code" value="USD">
<input type="hidden" name="bn" value="PP-DonationsBF:btn_donateCC_LG.gif:NonHostedGuest">
<input type="image" src="https://www.paypalobjects.com/WEBSCR-640-20110429-1/en_US/i/btn/btn_donateCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
<img alt="" border="0" src="https://www.paypalobjects.com/WEBSCR-640-20110429-1/en_US/i/scr/pixel.gif" width="1" height="1">
</form>
<br/><br/>
</center>

<? } else {
     _e("That download is not available at this time.", $i18n_domain);
   }
      if (0) {
        echo "$num_rows" . "<br/>\n";
        echo "$the_row->file_name" . "<br/>\n";
        echo "download ID = $val" . "<br/>\n";

        echo "DOCUMENT ROOT = " . $_SERVER['DOCUMENT_ROOT'] . "<br/>\n";
        echo "ARTISTOGRAPHY_DIR_NAME = " . ARTISTOGRAPHY_DIR_NAME . "<br/>\n";
        echo "Artistography Dir Name: " . ARTISTOGRAPHY_FILE_PATH . "<br/>\n";
        echo "home: " .get_option('home'). "<br/>\n";
        echo "site url: " .get_option('siteurl'). "<br/>\n";
        echo "Document Root: " .$_SERVER['DOCUMENT_ROOT']. "<br/>\n";
        echo "dirname(SERVER['SCRIPT_FILENAME']): " .dirname($_SERVER['SCRIPT_FILENAME']). "<br/>\n";
        echo "SCRIPT_NAME : " .$_SERVER['SCRIPT_NAME']. "<br/>\n";
      }
?>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<?php
get_sidebar();
get_footer();

      exit();
   }
}

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
  GLOBAL $wpdb, $TABLE_NAME, $download_path, $download_folder, $i18n_domain;
 
  $version = get_option('wp_artistography_version');

   /*** Store any options ***/
  if(!$version) {
     // this is a fresh install/activation
    add_option('wp_artistography_version', ARTISTOGRAPHY_VERSION, NULL, true);

  } else if (version_compare($version, "0.0.3-beta", '<')) {
     // this is an update
      $thetablev = $wpdb->prefix . $TABLE_NAME[TABLE_ARTISTS];
      $query = "ALTER TABLE '$thetable'
                DROP 'myspace_url'";
      $wpdb->query($query);
  }
  update_option('wp_artistography_version', ARTISTOGRAPHY_VERSION);

  if (!is_dir($download_path)) {
    mkdir($download_path);
  }

   // TODO: Link download.php instead, make sure we are providing the correct directory structure via variables
/*  if (!copy('/wp-content/plugins/artistography/download.php', '/download.php')) {
    wp_die( __('Failed to copy download.php to root directory.', $i18n_domain) );
  }
*/
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
                     birthday DATETIME,
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

        case TABLE_ARTIST_TRACK_LIST:
          $query .= "page_views INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     artist_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     album_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     artist_name TEXT NOT NULL,
                     album_name TEXT NOT NULL,
                     artist_url TEXT,
                     album_url TEXT,
                     picture_url TEXT NOT NULL,
                     number INT(10) NOT NULL,
                     name TEXT NOT NULL,
                     description TEXT,
                     url TEXT NOT NULL,
                     download_id INT(10) UNSIGNED DEFAULT '0' NOT NULL,
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
                     description LONGTEXT,
                     free_download_enabled BOOLEAN DEFAULT false NOT NULL,
                     featured BOOLEAN DEFAULT TRUE NOT NULL,
                     enabled BOOLEAN DEFAULT FALSE NOT NULL,";
          break;

        case TABLE_ARTIST_IMAGE_GALLERY:
          $query .= "page_views INT(10) UNSIGNED DEFAULT '0' NOT NULL,
                     artist_id INT(10),
                     picture_url TEXT NOT NULL,
                     description LONGTEXT,
                     enabled BOOLEAN DEFAULT FALSE NOT NULL,";
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

  if(folder_is_empty($download_path)) {
    rmdir($download_path);
  }

   // TODO: Remove download.php link, make sure we are deleting from correct directory via variables
  //delete('/download.php'); 

  if(!PRESERVE_DATABASE_TABLES) {
     //Delete any options that's stored also?
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

function artistography_init() {
  GLOBAL $i18n_domain, $artistography_plugin_dir;

  if(!artistography_is_current_version()) artistography_pluginInstall();

  load_plugin_textdomain( $i18n_domain, false, $artistography_plugin_dir );
}
add_action('init', 'artistography_init');

  define(ADMIN_MENU_STATS, __('Stats', $i18n_domain));
  define(ADMIN_MENU_OPTIONS, __('Options', $i18n_domain));
  define(ADMIN_MENU_MANAGE_ARTISTS, __('Manage Artists', $i18n_domain));
  define(ADMIN_MENU_MANAGE_MUSIC, __('Music Albums', $i18n_domain));
  define(ADMIN_MENU_MANAGE_ALBUM_DOWNLOADS, __('Album Downloads', $i18n_domain));
  define(ADMIN_MENU_MANAGE_DISCOGRAPHY, __('Discography', $i18n_domain));
//  define(ADMIN_MENU_MANAGE_GALLERIES, __('Galleries', $i18n_domain));
//  define(ADMIN_MENU_MANAGE_ALBUM_ART, __('Album Art', $i18n_domain));
  define(ADMIN_MENU_FTP_UPLOADER, __('FTP Uploader', $i18n_domain));
  define(ADMIN_MENU_ABOUT, __('About', $i18n_domain));

  define(TOP_LEVEL_HANDLE, 'artistography-top-level');
  define(SUBMENU_OPTIONS_HANDLE, 'artistography-submenu-options');
  define(SUBMENU_MANAGE_ARTISTS_HANDLE, 'artistography-submenu-manage-artists');
  define(SUBMENU_MANAGE_MUSIC_HANDLE, 'artistography-submenu-manage-music');
  define(SUBMENU_MANAGE_ALBUM_DOWNLOADS_HANDLE, 'artistography-submenu-manage-album-downloads');
  define(SUBMENU_MANAGE_DISCOGRAPHY_HANDLE, 'artistography-submenu-manage-discography');
//  define(SUBMENU_MANAGE_GALLERIES_HANDLE, 'artistography-submenu-manage-galleries');
//  define(SUBMENU_MANAGE_ALBUM_ART_HANDLE, 'artistography-submenu-manage-album-art');
  define(SUBMENU_FTP_UPLOADER, 'artistography-submenu-ftp-uploader');
  define(SUBMENU_ABOUT_HANDLE, 'artistography-submenu-about');

function artistography_enqueue_style_and_scripts() {
    wp_enqueue_style( 'jquery-ui', plugins_url('/js/jquery-ui-1.11.2/jquery-ui.css', $artistography_plugin_dir), array(), '1.0.0', 'all');
    wp_enqueue_style( 'jquery-ui', plugins_url('/js/jquery-ui-1.11.2/jquery-ui.theme.css', $artistography_plugin_dir), array(), '1.0.0', 'all');
    wp_enqueue_style( 'artistography', plugins_url('/css/style.css', $artistography_plugin_dir), array(), '1.0.0', 'all');
    wp_enqueue_script( 'jquery-ui',  plugins_url('/js/jquery-ui-1.11.2/jquery-ui.js', $artistography_plugin_dir), array( 'jquery' ), '1.0.0');
    wp_enqueue_script( 'artistography',  plugins_url('/js/admin.js', $artistography_plugin_dir), array( 'jquery-ui' ), '1.0.0');
}

 /* START ADMIN MENU INTERFACE */
add_action('admin_menu', 'artistography_plugin_menu');
function artistography_plugin_menu() {

  GLOBAL $artistography_plugin_dir, $i18n_domain;

  if( FALSE !== stripos($_GET['page'], 'artistography') ) {
    artistography_enqueue_style_and_scripts();
  }

  add_menu_page(ADMIN_MENU_STATS, __('Artistography', $i18n_domain), 'manage_options', TOP_LEVEL_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_STATS), ADMIN_MENU_STATS, 'manage_options', TOP_LEVEL_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_OPTIONS), ADMIN_MENU_OPTIONS, 'manage_options', SUBMENU_OPTIONS_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ARTISTS), ADMIN_MENU_MANAGE_ARTISTS, 'manage_options', SUBMENU_MANAGE_ARTISTS_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_MUSIC), ADMIN_MENU_MANAGE_MUSIC, 'manage_options', SUBMENU_MANAGE_MUSIC_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ALBUM_DOWNLOADS), ADMIN_MENU_MANAGE_ALBUM_DOWNLOADS, 'manage_options', SUBMENU_MANAGE_ALBUM_DOWNLOADS_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_DISCOGRAPHY), ADMIN_MENU_MANAGE_DISCOGRAPHY, 'manage_options', SUBMENU_MANAGE_DISCOGRAPHY_HANDLE, 'artistography_plugin_options');
//  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_GALLERIES), ADMIN_MENU_MANAGE_GALLERIES, 'manage_options', SUBMENU_MANAGE_GALLERIES_HANDLE, 'artistography_plugin_options');
//  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ALBUM_ART), ADMIN_MENU_MANAGE_ALBUM_ART, 'manage_options', SUBMENU_MANAGE_ALBUM_ART_HANDLE, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_FTP_UPLOADER), ADMIN_MENU_FTP_UPLOADER, 'manage_options', SUBMENU_FTP_UPLOADER, 'artistography_plugin_options');
  add_submenu_page(TOP_LEVEL_HANDLE, sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_ABOUT), ADMIN_MENU_ABOUT, 'manage_options', SUBMENU_ABOUT_HANDLE, 'artistography_plugin_options');

}

function artistography_plugin_options() {
  GLOBAL $wpdb, $i18n_domain, $title, $TABLE_NAME, $download_folder, $download_path, $ftpuploader_folder, $ftpuploader_path, $artistography_plugin_dir;

  if (!current_user_can('manage_options'))  {
    wp_die( __('You do not have sufficient permissions to access this page.', $i18n_domain) );
  }

  echo "<div class='wrap'>\n";
  echo "<h2>$title</h2>\n";
  switch($title) {
    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_STATS):
      require_once('admin/stats.php.inc');
      require_once('admin/download_stats.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_OPTIONS):
      require_once('admin/options.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ARTISTS):
      require_once('admin/manage_artists.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_MUSIC):
      require_once('admin/manage_music.php.inc');
      break;

    case sprintf(__('Artistography %s', $i18n_domain), ADMIN_MENU_MANAGE_ALBUM_DOWNLOADS):
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
