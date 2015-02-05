=== Artistography ===
Contributors: MistahWrite
Tags: artistography, artist, discography
Requires at least: 3.0.1
Tested up to: 4.1
Stabe tag: 0.0.7
License: GPLv2 or later
License URI: http://www.gnu.org/licenses/gpl-2.0.html

Artistography allows you to have a discography on a record label of artists with inter-linked featurings and collaborations among them, or outside artists.

== Description ==

Artistography allows a user to organize albums and videos onto an artist page.  The artist page has jQuery-UI style tabs, and polls tags on posts for the artist's name and then files them into the Related Posts tab.

== Installation ==

1. Install the Artisography plugin to your blog, and Activate it.  
2. Next, Enter an Artist into the Admin/Dashboard > Artistography > Artists
3. To populate the artist's Related Posts tab just tag posts with the Artist's name.  Artistography will automatically find it.
4. Use the following shortcodes on a page/post:

[artistography_display_artist_page id=1]
     Displays photo/bio, discography, videos, and related posts of artist with database id=1

[artistography_artist_name id=1]
     Displays the name of the artist with database id=1.

[artistography_display_enabled_artists]
     Displays "enabled" artists in a table with pictures that break away on mouse-over
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
