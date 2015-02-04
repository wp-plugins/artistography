<?php

 // Shortcode helpers
add_shortcode( 'artistography_display_enabled_albums', 'Music::shortCodeDisplayEnabledAlbums' );
add_shortcode( 'artistography_display_album', 'Music::shortCodeDisplayAlbum' );
add_shortcode( 'artistography_display_album_tracklist', 'Music::shortCodeDisplayAlbumTracklist' );
add_shortcode( 'artistography_display_album_artist', 'Music::shortCodeDisplayAlbumArtist' );

 // AJAX Administration
add_action('wp_ajax_Create_Album', 'Music::callback_Create_Album');
add_action('wp_ajax_Delete_Album', 'Music::callback_Delete_Album');

class Music
{
    protected static $artistTable = NULL;  // TABLE NAME of ARTIST TABLE
    protected static $musicTable = NULL;  // TABLE NAME of MUSIC ALBUM TABLE

     // property declaration
    public $id = NULL;
    public $enabled = NULL;

    public $artist_name = NULL;
    public $album_name = NULL;

    public $artist = NULL;
    public $artist_id = NULL;
    public $artist_url = NULL;
    public $picture_url = NULL;
    public $store_url = NULL;

    public $download_id = NULL;
    public $free_download_enabled = NULL;
    public $featured = NULL;
    public $description = NULL;

    public $album_year = NULL;
    public $album_month = NULL;
    public $album_day = NULL;
    public $album_date = NULL;

     // meta data property declarations
    public $last_updated_by_id = NULL;
    public $poster_id = NULL;
    public $create_date = NULL;
    public $update_date = NULL;

     // this class interfaces with the database
    protected $query = NULL;
    protected $query_result = NULL;
    protected $query_total_rows = NULL;
    protected $query_curr_node = NULL;

     // set funcs (protected)
    protected function setTotalRows ($rows) {    $this->query_total_rows = $rows;    }
    protected function setCurrNode ($node)  {    $this->query_curr_node = $node;    }

     // get funcs (public)
    public function getTotalRows ()   {    return $this->query_total_rows;    }
    public function getCurrNode ()    {    return $this->query_curr_node;    }
    public function getQueryResult () {    return $this->query_result;    }

    public static function callback_Create_Album(){
        GLOBAL $i18n_domain;

        $music = new Music;
/*        $music->insert($_POST['artist_id'],
                       $_POST['artist_name'],
                       $_POST['album_name'],
                       $music->formatDateTime($_POST['album_day'], $_POST['album_month'], $_POST['album_year']),
                       $_POST['artist_url'],
                       $_POST['picture_url'],
                       $_POST['store_url'],
                       $_POST['download_id'],
                       (strcmp($_POST['free_download_enabled'], NULL)) ? TRUE : FALSE,
                       (strcmp($_POST['featured'], NULL)) ? TRUE : FALSE,
                       $_POST['description'],
                       (strcmp($_POST['enabled'], NULL)) ? TRUE : FALSE);
*/
        if ($music->getTotalRows() <= 0) {
            _e("Failure...", $i18n_domain);  // failed
        } else {
            echo "1"; // success
        }

        unset($music);
        die;
    }

    public static function callback_Delete_Album(){
        GLOBAL $i18n_domain;

        $album_id = $_POST['album_id'];

        $music = new Music;
        $music->deleteById($album_id);

        $discography = new Discography;
        $discography->deleteByAlbumId($album_id);

        if ($music->getTotalRows() > 0) {
            echo "1"; // success
        } else {
            echo sprintf(__("Failed: Unable to Delete Album id: %u", $i18n_domain), $album_id);  // failed
        }

        unset($music);
        die;
    }

     // [artistography_display_enabled_albums cols="4"]
    public static function shortCodeDisplayEnabledAlbums( $atts ) {
	extract( shortcode_atts( array(
		'cols' => '1',
		'size' => '175'
	), $atts ) );

        $music = new Music;
        $html = "  <center>\n"
              . "    <table border='0'>\n";
            $num = $music->loadAllEnabled('album_date DESC')->getTotalRows();
        if ($num <= 0) {
            $html .= "    <tr><td colspan='" .esc_attr($cols). "' style='border:none;'>No Music Available in the Database!</td></tr>\n";
        } else {
            $rows = ((int)($num / esc_attr($cols)) < (float)($num / esc_attr($cols))) ? (int)($num / esc_attr($cols)) + 1 : (int)($num / esc_attr($cols));
            $width = esc_attr($size). "px";
            $height = esc_attr($size). "px";

            for ($i = 0; $i < $rows; $i++) {
                $html .= "      <tr>\n";
                for ($j = 0; $j < $cols AND ((($cols * ($i)) + ($j+1)) <= $num); $j++) {
                    $music->loadByNode(($i * $cols) + $j);
                    $html .= "        <td style='border:0;'>\n"
                          .  "          <div>\n"
                          .  "            <center><font style='font-size:8pt'>\n"
                          .  "            <a href='" .$music->artist_url. "'>" .$music->artist_name. "</a><br/>\n"
                          .  "            <a href='" .$music->store_url. "'>" .$music->album_name. "</a><br/>\n"
                          .  "            Released: <a href='" .$music->store_url. "'>" .$music->album_month.".".$music->album_day.".".$music->album_year. "</a><br/>\n"
                          .  "            <a href='" .$music->store_url. "' target='_blank'><img src='" .$music->picture_url. "' style='border:1px solid black;height:" .$height. ";width:" .$width. ";' /></a><br/>\n";
                    if ($music->download_id > 0) {
                        $html .= "            <a href='http://www.sprucegooserecords.com/download/$music->download_id' target='_blank'><img width='112' height='75' src='http://sprucegooserecords.com/images/download.icon.png' /></a>\n";
                    } else {
                        $html .= "            <div style='position:absolute;' width='112' height='75'>&nbsp;</div>\n";
                    }
                    $html .= "            </font></center>\n"
                          .  "          </div>\n"
                          .  "        </td>\n";
                }

                for ($j; $j < $cols; $j++) {
                    $html .= "<td>&nbsp;</td>\n";
                }
                $html .= "      </tr>\n";
                if ($i < ($rows-1)) {
                    $html .= "<tr><td colspan='" .esc_attr($cols). "'><hr style='width:100%;'></td></tr>\n";
                }
            }
        }
        $html .= "    </table>\n"
              .  "  </center>\n";

        unset($music);
        return $html;
    }

     // [artistography_display_album id="1"]
    public static function shortCodeDisplayAlbum ( $atts ) {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        $music = new Music;
        $music->loadById(esc_attr($id));

        $html = "Artist: $music->artist_name<br/>\n"
               . "Album: $music->album_name<br/>\n"
               . "Release Date: " .$music->album_month .".". $music->album_day .".". $music->album_year;

        unset($music);
        return $html;
    }

     // [artistography_display_album_tracklist id="1"]
    public static function shortCodeDisplayAlbumTracklist ( $atts ) {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        $music = new Music;
        $music->loadById(esc_attr($id));

        $html = $music->description;

        unset($music);
        return $html;
    }

     // [artistography_display_album_artist id="1"]
    public static function shortCodeDisplayAlbumArtist( $atts ) {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        $music = new Music;

        $html = $music->loadById(esc_attr($id))->album_year . " - " .$music->loadById(esc_attr($id))->artist_name. " - " .$music->loadById(esc_attr($id))->album_name;

        unset($music);
        return $html;
    }

    public function __construct() {
        GLOBAL $wpdb, $TABLE_NAME;

        self::$artistTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTISTS];
        self::$musicTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_MUSIC_ALBUMS];

        $this->loadAll();

        $this->artist = new Artist;
    }

    public function __destruct() {
        unset($this->artist);
    }

    protected function &loadCurrNodeValues () {
        GLOBAL $wpdb;

        if($this->getTotalRows() > 0) {
            $this->query_result = $wpdb->get_row($this->query, OBJECT, $this->getCurrNode());

             // meta data info update
            $this->id = $this->query_result->id;
            $this->poster_id = $this->query_result->poster_id;
            $this->last_updated_by_id = $this->query_result->last_updated_by_id;
            $this->create_date = $this->query_result->create_date;
            $this->update_date = $this->query_result->update_date;

            $this->album_name = stripslashes($this->query_result->album_name);
            $this->artist_name = stripslashes($this->query_result->artist_name);

            $this->artist_id = $this->query_result->artist_id;
            $this->artist_url = stripslashes($this->query_result->artist_url);
            $this->picture_url = stripslashes($this->query_result->picture_url);
            $this->description = stripslashes($this->query_result->description);
            $this->store_url = stripslashes($this->query_result->store_url);

            $this->album_date = $this->query_result->album_date;
            $this->album_year = date("Y", strtotime($this->album_date));
            $this->album_month = date("m", strtotime($this->album_date));
            $this->album_day = date("d", strtotime($this->album_date));

            $this->enabled = $this->query_result->enabled;

//            if ($this->enabled AND
//                ($this->album_year > date("Y") OR
//                ($this->album_year >= date("Y") AND $this->album_month > date("m")) OR
//                ($this->album_year >= date("Y") AND $this->album_month >= date("m") AND $this->album_day > date("d"))) ) {
//                $this->enabled = false;
//            }

            $this->download_id = $this->query_result->download_id;
            $this->free_download_enabled = $this->query_result->free_download_enabled;
            $this->featured = $this->query_result->featured;

            if($this->artist_id != 0) {
                $this->artist->loadById($this->artist_id);
            }
        }
        return $this;
    }

    public function formatDateTime($day, $month, $year, $hour = 0, $min = 0, $sec = 0) {
         // "YYYY-MM-DD HH:mm:SS";
        if(strlen($month) < 2) $month = "0$month";
        if(strlen($day) < 2) $day = "0$day";
        if(strlen($hour) < 2) $hour = "0$hour";
        if(strlen($min) < 2) $min = "0$min";
        if(strlen($sec) < 2) $sec = "0$sec";
        return "$year-$month-$day $hour:$min:$sec";
    }

    public function &getNodeNext () {
    // when this function is used, it's assumed that a query was already run
    // meant to simply load the nth item in the query through a for loop
    // assumes query, query_curr_node, and query_total_rows is set

        if (($this->query_curr_node + 1) <= $this->getTotalRows()) {
            $this->query_curr_node += 1;
            $this->loadCurrNodeValues();
        }
        return $this;
    }

    public function &getNodePrev () {
    // when this function is used, it's assumed that a query was already run
    // meant to simply load the nth item in the query through a for loop
    // assumes query, query_curr_node, and query_total_rows is set

        if (($this->query_curr_node - 1) >= 0 AND $this->getTotalRows() > 0) {
            $this->query_curr_node -= 1;
            $this->loadCurrNodeValues();
        }
        return $this;
    }

    public function &loadByNode ($node) {
    // when this function is used, it's assumed that a query was already run
    // meant to simply load the nth item in the query through a for loop

        if ($node < $this->getTotalRows() AND $node >= 0 AND $this->getTotalRows() > 0) {
            $this->setCurrNode($node);
            $this->loadCurrNodeValues();
        }
        return $this;
    }

    public function &loadById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM " .self::$musicTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAll ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$musicTable. "
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAllEnabled ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$musicTable. "
                        WHERE enabled = true
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAllDisabled ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$musicTable. "
                        WHERE enabled = false
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function incrementPageViewsById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
            "UPDATE " .self::$musicTable. "
             SET page_views = page_views + 1
             WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

    public function deleteById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$musicTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

     // update music album entry
    public function updateById ($music_id, $artist_id, $artist_name, $album_name, $album_date, $artist_url, $picture_url, $store_url, $download_id, $free_download_enabled, $featured, $description, $enabled) {
        GLOBAL $wpdb, $i18n_domain, $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
            "UPDATE " .self::$musicTable. "
             SET update_date = now(),
                 artist_id = %u,
                 artist_name = %s,
                 album_name = %s,
                 album_date = %s,
                 artist_url = %s,
                 picture_url = %s,
                 store_url = %s,
                 download_id = %u,
                 free_download_enabled = %b,
                 featured = %b,
                 description = %s,
                 enabled = %b,
                 last_updated_by_id = %u
             WHERE id = %u",
             $artist_id, $artist_name, $album_name, $album_date, $artist_url, $picture_url, $store_url, $download_id, $free_download_enabled, $featured, $description, $enabled, $current_user->ID, $music_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

    public function insert ($artist_id, $artist_name, $album_name, $album_date, $artist_url, $picture_url, $store_url, $download_id, $free_download_enabled, $featured, $description, $enabled) {
        GLOBAL $wpdb, $i18n_domain, $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                       "INSERT INTO " .(string)self::$musicTable. "
                        (create_date, update_date, poster_id, last_updated_by_id, artist_id, artist_name, album_name, album_date, artist_url, picture_url, store_url, download_id, free_download_enabled, featured, description, enabled)
                        VALUES (now(), now(), %u, %u, %u, %s, %s, %s, %s, %s, %s, %u, %b, %b, %s, %b)",
                        $current_user->ID, $current_user->ID, $artist_id, $artist_name, $album_name, $album_date, $artist_url, $picture_url, $store_url, $download_id, $free_download_enabled, $featured, $description, $enabled);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === 0 OR $this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return true;
        }
    }

    public function display_manage_music_form ($music_id = 0, $init_artist = '', $init_album = '', $init_day = 0, $init_month = 0, $init_year = 0, $init_picture_url = 'http://www.sprucegooserecords.com/', $init_artist_url = 'http://www.sprucegooserecords.com/store/', $init_store_url = 'http://www.sprucegooserecords.com/store/', $init_download_id = 0, $init_free_download = 1, $init_featured = 1, $init_description = '', $init_enabled = 1, $new = 1) {
        GLOBAL $wpdb, $TABLE_NAME, $i18n_domain;

        if ($init_day == 0) $init_day = (int)date("d");
        if ($init_month == 0) $init_month = (int)date("m");
        if ($init_year == 0) $init_year = (int)date("Y");

        $text_width = "400px";

        if ($new) { $fmusic = 'fmusic'; } else { $fmusic = 'fupdatemusic'; }
        echo "<form name='$fmusic' action='' method='post'>
              <table>
              <input type='hidden' name='music_id' value='$music_id' />
              <tr><td style='text-align:right;'>Artist:</td><td><input style='width:$text_width;' type='textbox' name='artist_name' value=\"$init_artist\" /></td></tr>
              <tr><td style='text-align:right;'>Album:</td><td><input style='width:$text_width;' type='textbox' name='album_name' value=\"$init_album\" /></td></tr>
              <tr><td style='text-align:right;'>Release Date:</td><td>
              <select name='album_day'>\n";

        for ($day=1; $day <= 31; $day++) {
            echo "<option value='" .date("d", mktime(date("H"), date("i"), date("s"), $month, $day, date("Y"))). "'";
            if($day == $init_day) echo " selected";
            echo ">$day</option>\n";
        }
        echo "</select>\n&nbsp;
              <select name='album_month'>\n";
        for ($month=1; $month <= 12; $month++) {
            echo "<option value='" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "'";
            if ($month == $init_month) echo " selected";
            echo ">" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))) ." - ". date("F", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "</option>\n";
        }
        echo "</select>\n&nbsp;
              <select name='album_year'>\n";
        for ($year=1+(int)date("Y"); $year >= 1990; $year--) {
            echo "<option value='" .$year. "'";
            if($year == $init_year) echo " selected";
            echo ">" .$year. "</option>\n";
        }
        echo "</select>
              </td></tr>\n";

        echo "<tr><td style='text-align:right;'>Album Art (Front) Hot Link (URL):</td><td><input style='width:$text_width;' type='textbox' name='picture_url' value=\"$init_picture_url\" /></td></tr>
              <tr><td style='text-align:right;'>Store URL:</td><td><input style='width:$text_width;' type='textbox' name='store_url' value=\"$init_store_url\" /></td></tr>
              <tr><td style='text-align:right;'>Artist URL:</td><td><input style='width:$text_width;' type='textbox' name='artist_url' value=\"$init_artist_url\" /></td></tr>\n";

        echo "<tr><td style='text-align:right;'>Download ID:</td>
                <td>
                  <select name='download_id'>\n";

        $thetable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_FILE_DOWNLOAD];
        $query = "SELECT *
                  FROM $thetable";
        $num = $wpdb->query($query);

        if($num === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $query) );
        } else {
            for ($i=0, $j=-1; $i <= $num; $i++, $j++) {
                if ($i > 0) {
                    $row = $wpdb->get_row($query, ARRAY_A, $j);
                    if ($i > 0) {
                        $id = $row['id'];
                        $file_name = $row['file_name'];
                        $download_count = $row['download_count'];
                        $arrayFile = explode("/", $file_name);
                        $arrayFile = array_reverse($arrayFile);
                        $file_name = $arrayFile[0];
                    }
                }
                echo "<option value='$i'";
                if ($i == $init_download_id) echo " selected";
                echo ">";
                echo ($i == 0) ? "Don't Link It Right Now" : "$id - $file_name";
                echo "</option>\n";
            }
        }
        echo "    </select>
                </td>
              </tr>
            <tr><td style='text-align:right;'>Free Download:</td><td><input style='width:$text_width' type='checkbox' name='free_download_enabled' ";
        if ($init_free_download) { echo 'checked'; }
        echo " /></td></tr>
              <tr><td style='text-align:right;'>Featured:</td><td><input style='width:$text_width' type='checkbox' name='featured' ";
        if ($init_featured) { echo 'checked'; }
        echo " /></td></tr>
              <tr><td style='text-align:right;'>Enabled:</td><td><input style='width:$text_width' type='checkbox' name='enabled' ";
        if ($init_enabled) { echo 'checked'; }
        echo " /></td></tr>
              <tr><td style='text-align:right;'>Description:</td><td><textarea name='description' style='width:100%;height:40em;'>" .stripslashes($init_description). "</textarea></td></tr>
              <tr><td colspan='2'></td></tr>\n";
        if ($new) {
            echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='new' value='Add New Album' /></td></tr>\n";
        } else {
            echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='update' value='Update Album' /></td></tr>\n";
        }
        echo "</table></form>\n";
    }
}  /* end class Music */
?>