<?php
      echo '<p>' .__('Thank you for using Artistography.  It was conceptualized in mid-2010, 
		and came to be manifested as a wordpress Plugin beginning around January 6th, 2011.
		  Developed by Chad Harrington (also known as Mistah Write.  
		It was developed with PHP 5, MySQL 5, and Wordpress v3.0.4<br/>><br/>
		== Shortcodes ==<br/>
			[artistography_artist_name]<br/>
			[artistography_display_enabled_artists]<br/>
			[artistography_display_artist]<br/>
			[artistography_display_artist_page]<br/>
			[artistography_album_download_link]<br/><br/>

			[artistography_album_art]<br/>
			[artistography_album_download_link]<br/><br/>

			[artistography_display_enabled_albums]<br/>
			[artistography_display_album]<br/>
			[artistography_display_album_tracklist]<br/>
			[artistography_display_album_artist]', $i18n_domain). '</p>';
      echo '<p>' .sprintf(__('Version: %s', $i18n_domain), ARTISTOGRAPHY_VERSION). '</p>';
?>
