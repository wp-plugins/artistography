<?php
 // Shortcode helpers
add_filter( 'the_posts', 'Artist::conditionally_add_scripts_and_styles'); // the_posts gets triggered before wp_head
add_shortcode( 'artistography_artist_name', 'Artist::shortCodeArtistName' );
add_shortcode( 'artistography_display_enabled_artists', 'Artist::shortCodeDisplayEnabledArtists' );
add_shortcode( 'artistography_display_artist', 'Artist::shortCodeDisplayArtist' );

 // AJAX Administration
add_action('wp_ajax_Create_Artist', 'Artist::callback_Create_Artist');
add_action('wp_ajax_Delete_Artist', 'Artist::callback_Delete_Artist');

class Artist
{
    protected static $artistTable = NULL;  // TABLE NAME of ARTIST TABLE

     // property declaration
    public $id = NULL;
    public $enabled = NULL;

    public $name = NULL;
    public $url = NULL;
    public $picture_url = NULL;
    public $myspace_url = NULL;
    public $description = NULL;
    public $birthday = NULL;

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

    public static function callback_Create_Artist(){
        GLOBAL $i18n_domain;

        $artist = new Artist;
/*        $artist->insert($_POST['artist_name'],
                        $_POST['url'],
                        $_POST['picture_url'],
                        $_POST['myspace_url'],
                        $artist->formatDateTime($_POST['artist_day'], $_POST['artist_month'], $_POST['artist_year']),
                        $_POST['artist_descr'],
                        (strcmp($_POST['enabled'], NULL)) ? TRUE : FALSE);
*/
        if ($artist->getTotalRows() <= 0) {
            _e("Failure...", $i18n_domain);  // failed
        } else {
            echo "1"; // success
        }

        unset($artist);
        die;
    }

    public static function callback_Delete_Artist(){
        GLOBAL $i18n_domain;

        $artist_id = $_POST['artist_id'];

        $artist = new Artist;
        $artist->deleteById($artist_id);

        $discography = new Discography;
        $discography->deleteByArtistId($artist_id);

        if ($artist->getTotalRows() > 0) {
            echo "1"; // success
        } else {
            echo sprintf(__("Failed: Unable to Delete Artist id: %u", $i18n_domain), $artist_id);  // failed
        }

        unset($artist);
        die;
    }

    public static function conditionally_add_scripts_and_styles($posts){
        GLOBAL $artistography_plugin_dir;
        if (empty($posts)) return $posts;
 
        $shortcode_found = false; // use this flag to see if styles and scripts need to be enqueued
        foreach ($posts as $the_post) {
            if (FALSE !== stripos($the_post->post_content, '[artistography_display_enabled_artists')) {
                $shortcode_found = true; // bingo!
                break;
            }
        }

        if ($shortcode_found) {
             // enqueue here
            wp_enqueue_style( 'jquery-ui', plugins_url('/css/jquery-ui.css', $artistography_plugin_dir), array(), '1.0.0', 'all');
            wp_enqueue_style( 'artistography', plugins_url('/css/style.css', $artistography_plugin_dir), array(), '1.0.0', 'all');
            wp_enqueue_script( 'jquery-ui',  plugins_url('/js/jquery-ui-1.8.9.js', $artistography_plugin_dir), array( 'jquery' ), '1.0.0'); 
            wp_enqueue_script( 'jquery-easing',  plugins_url('/js/jquery-easing.js', $artistography_plugin_dir), array( 'jquery' ), array( 'jquery' ), '1.0.0');
            wp_enqueue_script( 'artistography',  plugins_url('/js/script.js', $artistography_plugin_dir), array( 'jquery' ), array( 'jquery-u' ), '1.0.0');
        }
 
        return $posts;
    }

     // [artistography_artist_name id="1"]
    public static function shortCodeArtistName( $atts ) {
	extract( shortcode_atts( array(
		'id' => '1'
	), $atts ) );

        $artist = new Artist;
        $html = $artist->loadById(esc_attr($id))->name;
        unset($artist);
        return $html;
    }

     // [artistography_display_enabled_artists cols="4" size="75"]
    public static function shortCodeDisplayEnabledArtists( $atts ) {
	extract( shortcode_atts( array(
		'cols' => '2',
                'size' => '126'
	), $atts ) );

        $artist = new Artist;
        $discography = new Discography;
        $artist->loadAllEnabled('name');
        $num = $artist->getTotalRows();
        $html = "";

        $cols = esc_attr($cols);
        $rows = ((int)($num / $cols) < (float)($num / $cols)) ? (int)($num / $cols) + 1 : (int)($num / $cols);
        $height = esc_attr($size) .'px'; $width = esc_attr($size) .'px';

        $html .= "<center><div class='artist_table' style='display:none'>"
              .  "<table border='0'>";
        if ($num == 0) {
            $html .= "<tr>"
                  .  "  <td colspan='$cols' style='border:none;'>" .__('No Artists Available in the Database!', $i18n_domain). '</td>'
                  .  "</tr>";
        } else {
            for ( $i = 0; $i < $rows; $i++ ) {
                $html .= "      <tr>\n";
                for ( $j = 0; $j < $cols && ((($cols * ($i)) + ($j+1)) <= $num); $j++ ) {
                    $artist->loadByNode($i * $cols + $j);
                    $artist_albums = $discography->loadEnabledByArtistId($artist->id)->getTotalRows();
                    $video_posts = count($artist->getVideoPosts());
                    $related_posts = count($artist->getRelatedPosts());

                    $html .= "    <td style='border:0;'>"
                          .  "      <div height='" .esc_attr($size). "'>"
                          .  "        <div class='qitem' style='height:$height;width:$width'>"
                          .  "            <a href='" .$artist->url. "'><img src='" .$artist->picture_url. "' alt='" .$artist->name. "' title='' height='$height' width='$width' style='border:1px solid black;' /></a>"
                          .  "            <span class='caption' height='100%' width='100%'><h2>" .$artist->name. "</h2><p style='font-size:1.0em;'>";
                    if ($artist_albums > 0) {
                        $html .= sprintf(_n("%d Album", "%d Albums", $artist_albums), $artist_albums) . "<br/>\n";
                    }
                    if ($video_posts > 0) {
                        $html .= sprintf(_n("%d Video", "%d Videos", $video_posts), $video_posts) . "<br/>\n";
                    }
                    if ($related_posts > 0) {
                        $html .= sprintf(_n("%d Related Post", "%d Related Posts", $related_posts), $related_posts) . "<br/>\n";
                    }
                    $html .= "            </p></span>"
                          .  "        </div>"
                          .  "      </div>"
                          .  "    </td>";
                }
                for($j; $j < $cols; $j++) {
                    $html .= "<td>&nbsp;</td>\n";
                }
                $html .= "  </tr>\n";
                if ($i < ($rows-1)) { $html .= "<tr><td colspan='$cols'><hr style='width:100%;'></td></tr>\n"; }
            }
        }
        $html .= "</table></div></center>";
        unset($artist);
        unset($discography);
        return $html;
    }

     // [artistography_display_artist id="1"]
    public static function shortCodeDisplayArtist( $atts ) {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        $artist = new Artist;

        $html = $artist->loadById(esc_attr($id))->name;

        unset($artist);
        return $html;
    }

    public function __construct() {
        GLOBAL $wpdb, $TABLE_NAME;

        self::$artistTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTISTS];

        $this->loadAll();
    }

    public function __destruct() {
        /* This is a placeholder just in case it's needed eventually */
    }

    protected function &loadCurrNodeValues () {
        GLOBAL $wpdb, $_SERVER;

        if ($this->getTotalRows() > 0) {
            $this->query_result = $wpdb->get_row($this->query, OBJECT, $this->getCurrNode());

             // meta data info update
            $this->id = $this->query_result->id;
            $this->enabled = $this->query_result->enabled;
            $this->poster_id = $this->query_result->poster_id;
            $this->last_updated_by_id = $this->query_result->last_updated_by_id;
            $this->create_date = $this->query_result->create_date;
            $this->update_date = $this->query_result->update_date;

            $this->name = $this->query_result->name;
//            $this->url = $this->query_result->url;
            $this->url = "http://" .$_SERVER['SERVER_NAME'] . "/wp/artists/" . strtolower(str_replace(' ', '-', str_replace('& ', '', str_replace('.', '', $this->name))));
            $this->picture_url = $this->query_result->picture_url;
            $this->myspace_url = $this->query_result->myspace_url;
            $this->description = $this->query_result->description;
            $this->birthday = $this->query_result->birthday;
        } else {
            $this->query_result = 

            $this->id = 
            $this->enabled = 
            $this->poster_id = 
            $this->last_updated_by_id = 
            $this->create_date = 
            $this->update_date = 

            $this->name = 
            $this->url = 
            $this->picture_url = 
            $this->myspace_url = 
            $this->description = 
            $this->birthday = 0;
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
                        FROM " .self::$artistTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAll ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$artistTable. "
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAllEnabled ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$artistTable. "
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
                        FROM " .self::$artistTable. "
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
            "UPDATE " .self::$artistTable. "
             SET page_views = page_views + 1
             WHERE id = %u",
             $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

     /* Get posts in "Videos" category via tags */
    public function getVideoPosts ($order_by='date') {
        $cat_id = get_term_by('name', 'Videos', 'category')->term_id;
        $args = array('tag' => strtolower(str_replace("&", "", str_replace(" ", "-", str_replace(".", "-", str_replace("& ", "", $this->name))))),
                      'orderby' => $order_by,
                      'numberposts' => -1);
        $posts = get_posts($args);
        foreach ($posts as $key => $value) {
            if(!in_category($cat_id, $value)) {
                unset($posts[$key]);
            }
        }
        return $posts;
    }

     /* Get posts in all categories (except "Videos") via tags */
    public function getRelatedPosts ($order_by='date') {
        $cat_id = get_term_by('name', 'Videos', 'category')->term_id;
        $args = array('tag' => strtolower(str_replace("&", "", str_replace(" ", "-", str_replace(".", "-", str_replace("& ", "", $this->name))))),
                      'orderby' => $order_by,
                      'numberposts' => -1);
        $posts = get_posts($args);
        foreach ($posts as $key => $value) {
            if(in_category($cat_id, $value)) {
                unset($posts[$key]);
            }
        }
        return $posts;
    }

    public function deleteById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$artistTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

     // update artist entry
    public function updateById ($artist_id, $artist_name, $url, $picture_url, $myspace_url, $birthday, $artist_descr, $enabled) {
        GLOBAL $wpdb, $i18n_domain;
        GLOBAL $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                 "UPDATE " .self::$artistTable. "
                  SET update_date = now(),
                      name = %s,
                      url = %s,
                      picture_url = %s,
                      myspace_url = %s,
                      description = %s,
                      birthday = %s,
                      enabled = %s,
                      last_updated_by_id = %u
                  WHERE id = %s",
                  $artist_name, $url, $picture_url, $myspace_url, $artist_descr, $birthday, $enabled, $current_user->ID, $artist_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

    public function insert ($artist_name, $url, $picture_url, $myspace_url, $birthday, $artist_descr, $enabled) {
        GLOBAL $wpdb, $i18n_domain;
        GLOBAL $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                       "INSERT INTO " .self::$artistTable. "
                        (create_date, update_date, poster_id, last_updated_by_id, name, url, picture_url, myspace_url, birthday, description, enabled)
                        VALUES (now(), now(), %u, %u, %s, %s, %s, %s, %s, %s, %b)",
                        $current_user->ID, $current_user->ID, $artist_name, $url, $picture_url, $myspace_url, $birthday, $artist_descr, $enabled);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === 0 OR $this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return true;
        }
    }

    public function display_manage_artist_form ($artist_id = 0, $init_artist = '', $init_day = 0, $init_month = 0, $init_year = 0, $init_picture_url = 'http://www.sprucegooserecords.com/', $init_url = 'http://www.sprucegooserecords.com/', $init_myspace_url = '', $init_artist_descr = '', $init_enabled = false, $new = 1) {

        if ($init_day == 0) $init_day = (int)date("d");
        if ($init_month == 0) $init_month = (int)date("m");
        if ($init_year == 0) $init_year = (int)date("Y");

        $text_width = "400px";

        if ($new) { $fartist = 'fartist'; } else { $fartist = 'fupdateartist'; }
        echo "<form name='$fartist' action='' method='post'>
              <table>\n
              <input type='hidden' name='artist_id' value='$artist_id' />\n
              <tr><td style='text-align:right;'>Artist:</td><td><input style='width:$text_width;' type='textbox' name='artist_name' value='$init_artist' /></td></tr>\n
              <tr><td style='text-align:right;'>Birthday:</td><td>\n
              <select name='artist_day'>\n";
        for($day=1; $day <= 31; $day++) {
            echo "<option value='" .date("d", mktime(date("H"), date("i"), date("s"), $month, $day, date("Y"))). "'";
            if($day == $init_day) echo " selected";
            echo ">$day</option>\n";
        }
        echo "</select>\n&nbsp;
              <select name='artist_month'>\n";
        for($month=1; $month <= 12; $month++) {
            echo "<option value='" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "'";
            if ($month == $init_month) echo " selected";
            echo ">" .date("m", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))) ." - ". date("F", mktime(date("H"), date("i"), date("s"), $month, date("j"), date("Y"))). "</option>\n";
        }
        echo "</select>\n&nbsp;
              <select name='artist_year'>\n";
        for ($year=1+(int)date("Y"); $year >= 1930; $year--) {
            echo "<option value='" .$year. "'";
            if($year == $init_year) echo " selected";
            echo ">" .$year. "</option>\n";
        }
        echo "</select>\n
            </td></tr>\n";

        echo "<tr><td style='text-align:right;'>Picture (URL):</td><td><input style='width:$text_width;' type='textbox' name='picture_url' value=\"$init_picture_url\" /></td></tr>\n
              <tr><td style='text-align:right;'>Artist (URL):</td><td><input style='width:$text_width;' type='textbox' name='url' value=\"$init_url\" /></td></tr>\n
              <tr><td style='text-align:right;'>MySpace (URL):</td><td><input style='width:$text_width;' type='textbox' name='myspace_url' value=\"$init_myspace_url\" /></td></tr>\n
              <tr><td style='text-align:right;'>Enabled:</td><td><input style='width:$text_width;' type='checkbox' name='enabled' " .(($init_enabled) ? "checked" : ""). " /></td></tr>\n
              <tr><td style='text-align:right;'>Description:</td><td><textarea name='artist_descr'>$init_artist_descr</textarea></td></tr>\n
              <tr><td colspan='2'></td></tr>\n";
        if ($new) {
            echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='new' value='Add New Artist' /></td></tr>\n";
        } else {
            echo "<tr><td colspan='2' style='text-align:center;'><input type='submit' name='update' value='Update Artist' /></td></tr>\n";
        }

        echo "</table></form>\n";
    }
}  /* end class Artist */

?>