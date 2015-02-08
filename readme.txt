=== Artistography ===
Contributors: MistahWrite
Tags: artistography, artist, discography
Requires at least: 3.0.1
Tested up to: 4.1
Stabe tag: 0.1.1
License: GPLv2 or later
License URI: http://www.gnu.org/licenses/gpl-2.0.html

Artistography allows you to have a discography on a record label of artists with inter-linked featurings and collaborations among them, or outside artists.

== Description ==

Artistography allows a user to organize albums and videos onto an artist page.  The artist page has jQuery-UI style tabs, and polls tags on posts for the artist's name and then files them into the Related Posts tab.

Uses for FTP and file browsing capability:
 * http://sourceforge.net/projects/encode-explorer/ (version 6.3)
 * http://sourceforge.net/projects/zupload/ 

== Installation ==

1. Install the Artisography plugin to your blog, and Activate it.  
2. Next, Enter an Artist into the Admin/Dashboard > Artistography > Artists
3. To populate the artist's Related Posts tab just tag posts with the Artist's name.  Artistography will automatically find it.
4. Use the following shortcodes on a page/post:

[artistography_display_artist_page id=1]
     Displays photo/bio, discography, videos, and related posts of artist with database id=1

[artistography_artist_name id=1]
     Displays the name of the artist with database id=1.

[artistography_display_artists]
     Displays artists in a table with pictures that break away on mouse-over
          Optional paramaters:
               cols=(default 4)

[artistography_display_artist]
     

[artistography_album_download_link id=1]
     Displays a download picture with link to download album of album with database id=1

[artistography_album_art id=1]
     Displays album photo for album with database id=1

[artistography_display_enabled_albums]
     Displays "enabled" albums in a table with associated download hyperlink (if linked to a download)
          Optional paramters:
               cols=(default 4)
[artistography_display_album]
     
[artistography_display_album_tracklist id=1]
     Displays tracklist/description of album with album database id=1
[artistography_display_album_artist id=1]
     Displays artist name of album with album database id=1

== Changelog ==

=0.1.1=
* Fixed options screen
* Used preserve_database option in uninstall
* Fixed delete track_list database table
* Fixed install script logic

=0.1.0=
* Added ZUpload from sourceforge instead of unlimited_ftp
* Added eXtplorer 2.1.5 from sourceforge for PHP file browser
* Fixed options screen

=0.0.9=
* Removed track_list database and support routines
* Removed stats page
* Moved Options page towards the bottom
* Made textbox into textarea for artist description
* Fixed FTP Uploader page with plugs_url()

=0.0.8=
* Updated style for admin panels
* Worked on AJAX Artist Create, Edit, Update, and Delete Artist
* Dropped artist birthday from database
* Dropped support for regular post methods for artist create, edit, and update
* Preparing for full internationalization support
* Finally using $artist->incrementPageViewsById($id) when shortcode is used: [artistography_display_artist_page id=x]
* Displaying artist page views in manage artist admin panel

=0.0.7-alpha=
* Fixed Related Posts size so that accordions would be visible

= 0.0.7 =
* Split up css for admin and display site

= 0.0.6 =
* Added function: artistography_enqueue_admin_style_and_scripts()

= 0.0.5 =
* Fixed broken css/javascript include path: artistography_enqueue_style_and_scripts

= 0.0.4 =
* More internationalization support.

= 0.0.3 =
* Removed myspace_url support from artist database table
* Added function: artistography_enqueue_style_and_scripts()

= 0.0.2 =
* Internationalization support begun
* Updated jQuery and jQuery-UI to version 1.11.2

= 0.0.1 =
* Created Project "Artistography"
* Setup Top-Level Menu in the Admin panel, with submenus
