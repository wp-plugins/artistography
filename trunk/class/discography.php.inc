<?php
 // Shortcode helpers
add_filter( 'the_posts', 'Discography::conditionally_add_scripts_and_styles'); // the_posts gets triggered before wp_head
add_shortcode( 'artistography_display_artist_page', 'Discography::shortCodeDisplayArtistPage' );
add_shortcode( 'artistography_album_download_link', 'Discography::shortCodeAlbumDownloadLink' );
add_shortcode( 'artistography_album_art', 'Discography::shortCodeAlbumArt' );


 // AJAX Administration Drag/Drop Discography Auto-Save feature
add_action('wp_ajax_Connect_Artist_to_Album', 'Discography::callback_Connect_Artist_to_Album');
add_action('wp_ajax_Disconnect_Artist_from_Album', 'Discography::callback_Disconnect_Artist_from_Album');

class Discography
{
    protected static $artistTable = NULL;  // TABLE NAME of ARTIST TABLE
    protected static $musicTable = NULL;  // TABLE NAME of MUSIC ALBUM TABLE
    protected static $discographyTable = NULL;  // TABLE NAME of MUSIC ALBUM TABLE

     // property declaration
    public $id = NULL;

    public $artist_id = NULL;
    public $album_id = NULL;

    public $artist = NULL;
    public $album = NULL;

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

    public function __construct() {
        GLOBAL $wpdb, $TABLE_NAME;

        self::$artistTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTISTS];
        self::$musicTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_MUSIC_ALBUMS];
        self::$discographyTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_ALBUM_LINKER];

        $this->loadAll();

        $this->artist = new Artist;
        $this->album = new Music;
    }

    public function __destruct() {
        unset($this->artist);
        unset($this->album);
    }

    public static function callback_Connect_Artist_to_Album(){
        GLOBAL $i18n_domain;

        $artist_id = $_POST['artist_id'];
        $album_id = $_POST['album_id'];

        $discography = new Discography;
        $discography->loadAllByArtistAlbum($artist_id, $album_id);

        if ($discography->getTotalRows() > 0) {
            _e("The Artist is already attached to that album.", $i18n_domain);  // failed
        } else {
            $discography->insert($artist_id, $album_id);
            echo "1"; // success
        }

        unset($discography);
        die;
    }

    public static function callback_Disconnect_Artist_from_Album(){
        GLOBAL $i18n_domain;

        $artist_id = $_POST['artist_id'];
        $album_id = $_POST['album_id'];

        $discography = new Discography;
        $discography->loadAllByArtistAlbum($artist_id, $album_id);

        if ($discography->getTotalRows() > 0) {
            $discography->deleteById($discography->id);
            echo "1"; // success
        } else {
            _e("Failed to Disconnect Artist from Album as it appears there currently is no connection between them on the server.  "
             . "It's possible another administrator may be using this feature at the same time.", $i18n_domain);  // failed
        }

        unset($discography);
        die;
    }

    public static function conditionally_add_scripts_and_styles($posts){
        GLOBAL $artistography_plugin_dir;
        if (empty($posts)) return $posts;
 
        $shortcode_found = false; // use this flag to see if styles and scripts need to be enqueued
        foreach ($posts as $the_post) {
            if (FALSE !== stripos($the_post->post_content, '[artistography_display_artist_page')) {
                $shortcode_found = true; // bingo!
                break;
            }
        }

        if ($shortcode_found) {
             // enqueue here
             artistography_enqueue_style_and_scripts();
        }
 
        return $posts;
    }

     // [artistography_album_art id=""]
    public static function shortCodeAlbumArt( $atts, $content=null, $code="") {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        GLOBAL $i18n_domain;

        $id = esc_attr($id);

        $discography = new Discography;
        $artist = new Artist;
        $album = new Music;
        $html = "";

        $html = "[caption id=\"attachment_557\" align=\"alignleft\" width=\"300\" caption=\"Dr. Oscify Breathe Easy Soon\"]<a href=\"http://www.sprucegooserecords.com/wp-content/uploads/2011/05/DrOscify-Breathe-Easy-Soon.jpg\"><img class=\"size-medium wp-image-557\" title=\"Dr. Oscify Breathe Easy Soon\" src=\"http://www.sprucegooserecords.com/wp-content/uploads/2011/05/DrOscify-Breathe-Easy-Soon-300x300.jpg\" alt=\"\" width=\"300\" height=\"300\" /></a>[/caption]\n";

        unset($discography);
        unset($artist);
        unset($album);
        return do_shortcode($html);
    }

     // [artistography_album_download_link id=""]
    public static function shortCodeAlbumDownloadLink( $atts, $content=null, $code="") {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        GLOBAL $i18n_domain;

        $id = esc_attr($id);

//        $discography = new Discography;
//        $artist = new Artist;
        $album = new Music;
        $html = "";
        $album->loadById($id);

        $html = "<p style='text-align: center;'><a href='http://www.sprucegooserecords.com/download/$album->download_id' target='_blank'><img class='aligncenter size-full wp-image-529' title=\"Download &quot;$album->album_name&quot; by $album->artist_name\" src='http://www.sprucegooserecords.com/wp-content/uploads/2011/05/download.icon_.png' alt=\"Download &quot;$album->album_name&quot; by $album->artist_name\" width='183' height='122' /></a></p>\n";

//        unset($discography);
//        unset($artist);
        unset($album);
        return $html;
    }


     // [artistography_display_artist_page id="4" gid="1"]
    public static function shortCodeDisplayArtistPage( $atts, $content=null, $code="") {
	extract( shortcode_atts( array(
		'id' => '0',
		'gid' => '0'
	), $atts ) );

        GLOBAL $i18n_domain;

        $id = esc_attr($id);
        $gid = esc_attr($gid);

        $discography = new Discography;
        $artist = new Artist;
        $album = new Music;
        $html = "";

        if ($artist->loadById($id)->getTotalRows() > 0) {
            $artist->incrementPageViewsById($id);
            $discography->loadEnabledByArtistId($id);
            $num = $discography->getTotalRows();
            $video_postslist = $artist->getVideoPosts();
            $related_postslist = $artist->getRelatedPosts();

            $html .= "<div id='tabs' style='display:none'>\n"
                  .  "  <ul>\n"
                  .  "    <li><a href='#tabs-1'>About</a></li>\n";
            if ($num > 0) {
                $html .= "    <li><a href='#tabs-2'>Music (" .$num. ")</a></li>\n";
            }

            if ( !empty($video_postslist) ) {
                $html .= "    <li><a href='#tabs-3'>Videos (" .count($video_postslist). ")</a></li>\n";
            }

            if ( !empty($related_postslist) ) {
                $html .= "    <li><a href='#tabs-4'>Related Posts (" .count($related_postslist). ")</a></li>\n";
            }

            if ($gid != 0) {
//                $html .= "    <li><a href='#tabs-5'>Images</a></li>\n";
            }
            $html .= "  </ul>\n"
                  .  "  <div id='tabs-1'>\n";
             /*** DISPLAY ARTIST ABOUT TAB ***/
            $html .= "    <p><table width='100%' border='1'><tr><td><img src='" .stripslashes($artist->picture_url)
                  .  "' height='225' width='225' align='left' style='margin-right:1.0em;overflow:auto;' />\n";
            if(empty($content)) {
                $html .= stripslashes($artist->description). "\n";
            } else {
                $html .= do_shortcode($content). "</p>\n";
            }
            $html .= "  </td></tr></table></div>\n";

             /*** DISPLAY THE MUSIC/DISCOGRAPHY TAB ***/
            if ($num > 0) {
                $cols = 1;
                $rows = ((int)($num / $cols) < (float)($num / $cols)) ? (int)($num / $cols) + 1 : (int)($num / $cols);
                $width = '225px';
                $height = '225px';
                $html .= " <div id='tabs-2'>\n"
                      .  "<center><table border='0'>";
                for ($i = 0; $i < $rows; $i++) {
                    $html .= "<tr>\n";
                    $j = 0;
                    for($j = 0; $j < $cols && ((($cols * ($i)) + ($j+1)) <= $num); $j++) {
                        $discography->loadByNode($i * $cols + $j);
                        $artist->loadById($discography->artist_id);
                        $album->loadById($discography->album_id);
                        $html .= "  <td style='border:0;'>"
                              .  "     <center><font style='font-size:8pt'>"
                              .  "       <a href='$album->artist_url'>$album->artist_name</a><br/>"
                              .  "       <a href='$album->store_url'>$album->album_name</a><br/>"
                              .  "       Released: <a href='$album->store_url'>"
                              .  $album->album_month. "." .$album->album_day. "." .$album->album_year
                              .  "       </a><br/>"
                              .  "       <a href='$album->store_url'>"
                              .  "        <img src='$album->picture_url' style='border:1px solid black;height:$height;width:$width;' /></a><br/>";
                        if ($album->download_id > 0) {
                            $html .= "       <a href='/download/$album->download_id'>"
                                  .  "        <img width='112' height='75' src='/images/download.icon.png' /></a>";
                        }
                        $html .= "    </font></center>"
                              .  "  </td>"
                              .  "  <td style='border:0;'>"
                              .  "    <div class='tracklist'><font style='font-size:8pt;text-align:left;'>"
                              .  do_shortcode($album->description)
                              .  "    </font></div>"
                              .  "  </td>";
                    }
                    for($j; $j < $cols; $j++) {
                        $html .= "<td>&nbsp;</td>\n";
                    }
                    $html .= "      </tr>\n";
                    if ($i < ($rows-1)) { $html .= "<tr><td colspan='" .($cols*2). "'><hr style='width:100%;'></td></tr>\n"; }
                }
                $html .= "</table>"
                      .  "</center>"
                      .  "</div>";
            }

             /*** DISPLAY VIDEOS TAB ***/
            if ( !empty($video_postslist) ) {
                $html .= "  <div id='tabs-3'>\n"
                      .  "    <div id='accordion2'>\n";
                foreach ($video_postslist as $post) {
                    $comment_array = get_approved_comments($post->ID);
                    $comment_counter = 0;
                    foreach($comment_array as $comment){
                        $comment_counter += 1;
                    }
                    $html .= "    <h3><a href='#'>$post->post_title</a></h3>\n"
                          .  "    <div><table><tr><td>" .do_shortcode($post->post_content). "</td></tr>"
                          .  "    <tr><td><hr width='100%' /></td></tr>"
                          .  "    <tr><td><a href='"
                          .  get_permalink($post->ID). "'>Permalink</a> | <a href='"
                          .  get_permalink($post->ID). "'>Comments (" .$comment_counter. ")</a></td></tr>"
                          .  "    </table></div>\n";
                }
                $html .= "    </div>\n"
                      .  "  </div>\n";
            }

             /*** DISPLAY RELATED POSTS TAB ***/
            if ( !empty($related_postslist) ) {
                $html .= "  <div id='tabs-4'>\n"
                      .  "    <div id='accordion3'>\n";
                foreach ($related_postslist as $post) {
                    $html .= "    <h3><a href='#'>$post->post_title</a></h3>\n"
                          .  "    <div><p><table><tr><td>" .do_shortcode($post->post_content). "</td></tr>"
                          .  "    <tr><td><hr width='100%'></td></tr>"
                          .  "    <tr><td><a href='" .get_permalink($post->ID). "' target='_blank'>Permalink</a>: " .get_permalink($post->ID). "</td></tr>"
                          .  "    </table></p></div>\n";
                }
                $html .= "    </div>\n"
                      .  "  </div>\n";
            }

            if ($gid != 0) {
                $html .= "  <div id='tabs-5'>\n";
//                $html .= do_shortcode('[gallery id=' .$gid. ']');
                $html .= "  </div>\n";
            }
            $html .= "</div>\n";
        } else if ($id == '0') {
	    $html .= __('Error: Artist ID specified in Artistography shortcode not found in database.  First artist is always id=1 not id=0.', $i18n_domain);

	} else {
            $html .= __('Error: Artist ID specified in Artistography shortcode not found in database.', $i18n_domain);
        }

        unset($discography);
        unset($album);
        unset($artist);
        return do_shortcode($html);
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

    protected function &loadCurrNodeValues () {
        GLOBAL $wpdb;

        if ($this->getTotalRows() > 0) {
            $this->query_result = $wpdb->get_row($this->query, OBJECT, $this->getCurrNode());

             // meta data info update
            $this->id = $this->query_result->id;
            $this->poster_id = $this->query_result->poster_id;
            $this->last_updated_by_id = $this->query_result->last_updated_by_id;
            $this->create_date = $this->query_result->create_date;
            $this->update_date = $this->query_result->update_date;

            $this->artist_id = $this->query_result->artist_id;
            $this->album_id = $this->query_result->album_id;

            if($this->artist_id > 0) {
//                $this->artist->loadById($this->artist_id);
            }

            if($this->album_id > 0) {
//                $this->album->loadById($this->album_id);
            }
        } else {
            $this->query_result = 

            $this->id =
            $this->poster_id =
            $this->last_updated_by_id =
            $this->create_date =
            $this->update_date =

            $this->artist_id =
            $this->album_id = 0;
        }
        return $this;
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
                        FROM  " .self::$discographyTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadByArtistId ($artist_id, $order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. "
                        WHERE artist_id = %u
                        ORDER BY $order_by",
                        $artist_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadEnabledByArtistId ($artist_id, $order_by = 'album_date DESC') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. " dt
                  RIGHT JOIN  " .self::$musicTable. " mt
                          ON  dt.album_id = mt.id
                       WHERE  dt.artist_id = %u
                         AND  mt.enabled = true
                    ORDER BY  $order_by",
                        $artist_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadByAlbumId ($album_id, $order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. "
                        WHERE album_id = %u
                        ORDER BY $order_by",
                        $album_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAllByArtistAlbum ($artist_id, $album_id, $order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. "
                        WHERE artist_id = %u
                          AND album_id = %u
                        ORDER BY $order_by",
                        $artist_id, $album_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadDisabledByArtistAlbum ($artist_id, $album_id, $order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. "
                        WHERE enabled = false
                          AND artist_id = %u
                          AND album_id = %u
                        ORDER BY $order_by",
                        $artist_id, $album_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadEnabledByArtistAlbum ($artist_id, $album_id, $order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM  " .self::$discographyTable. "
                        WHERE enabled = true
                          AND artist_id = %u
                          AND album_id = %u
                        ORDER BY $order_by",
                        $artist_id, $album_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAll ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$discographyTable. "
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function deleteById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$discographyTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

    public function deleteByArtistId ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$discographyTable. "
                        WHERE artist_id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

    public function deleteByAlbumId ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$discographyTable. "
                        WHERE album_id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

     // update music album entry
    public function updateById ($discography_id, $artist_id, $album_id) {
        GLOBAL $wpdb, $i18n_domain, $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
            "UPDATE " .self::$discographyTable. "
             SET update_date = now(),
                 artist_id = %u,
                 album_id = %u,
                 last_updated_by_id = %u
             WHERE id = %u",
             $artist_id, $album_id, $current_user->ID, $discography_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

    public function insert ($artist_id, $album_id) {
        GLOBAL $wpdb, $i18n_domain, $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                       "INSERT INTO " .(string)self::$discographyTable. "
                        (create_date, update_date, poster_id, last_updated_by_id, artist_id, album_id)
                        VALUES (now(), now(), %u, %u, %u, %u)",
                        $current_user->ID, $current_user->ID, $artist_id, $album_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === 0 OR $this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return true;
        }
    }

}  /* end class Discography */
?>
