<?php
 // Shortcode helpers
add_filter( 'the_posts', 'Song::conditionally_add_scripts_and_styles'); // the_posts gets triggered before wp_head
add_shortcode( 'artistography_display_song', 'Song::shortCodeDisplaySong' );

 // AJAX Administration
add_action('wp_ajax_Create_Song', 'Song::callback_Create_Song');
add_action('wp_ajax_Update_Song', 'Song::callback_Update_Song');
add_action('wp_ajax_Edit_Song', 'Song::callback_Edit_Song');
add_action('wp_ajax_Delete_Song', 'Song::callback_Delete_Song');

class Song
{
    protected static $songTable = NULL;  // TABLE NAME of ARTIST TABLE

     // property declaration
    public $id = NULL;

    public $artist_id = NULL;
    public $name = NULL;
    public $url = NULL;
    public $price = NULL;

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

    public static function callback_Create_Song(){
        GLOBAL $i18n_domain;

        $song = new Song;

        $artist_id = stripslashes($_POST['artist_id']);
	$song_name = stripslashes($_POST['song_name']);
        $url = stripslashes($_POST['url']);
	$price = stripslashes($_POST['price']);

        $result = $song->insert($artist_id, $song_name, $url, $price);
        if(is_numeric($result)) {
          echo $result;
        } else {
          echo sprintf(__("Failed: %s", $i18n_domain), $result);  // failed
        }

        unset($song);
        die;
    }

    public static function callback_Update_Song(){
        GLOBAL $i18n_domain;

        $song = new Song;

	$song_id = stripslashes($_POST['song_id']);
        $artist_id = stripslashes($_POST['artist_id']);
	$song_name = stripslashes($_POST['song_name']);
        $url = stripslashes($_POST['url']);
	$price = stripslashes($_POST['price']);

        if($song->updateById ($song_id, $artist_id, $song_name, $url, $price) ) {
          echo '1'; //success
        } else {
          echo sprintf(__("Failed: Unable to Update Artist id: %u", $i18n_domain), $artist_id);
        }

        unset($song);
        die;
    }

    public static function callback_Edit_Song(){
        GLOBAL $i18n_domain;

        $song = new Song;

        if($song->loadById($_POST['song_id'])->getTotalRows() > 0) {

          echo $song->id
		."##$$##". stripslashes($song->artist_id)
                ."##$$##". stripslashes($song->name)
              	."##$$##".  stripslashes($song->url)
		."##$$##". stripslashes($song->price);
        }

        unset($song);
        die;
    }

    public static function callback_Delete_Song(){
        GLOBAL $i18n_domain;

        $song_id = $_POST['song_id'];

        $song = new Song;
        $song->deleteById($song_id);

//        $discography = new Discography;
//        $discography->deleteByArtistId($artist_id);

        if ($song->getTotalRows() > 0) {
            echo "1"; // success
        } else {
            echo sprintf(__("Failed: Unable to Delete Artist id: %u", $i18n_domain), $artist_id);  // failed
        }

        unset($songt);
        die;
    }

    public static function conditionally_add_scripts_and_styles($posts){
        GLOBAL $artistography_plugin_dir;
        if (empty($posts)) return $posts;
 
        $shortcode_found = false; // use this flag to see if styles and scripts need to be enqueued
        foreach ($posts as $the_post) {
            if (FALSE !== stripos($the_post->post_content, '[artistography_display_song')) {
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

     // [artistography_display_song id="1"]
    public static function shortCodeDisplaySong( $atts ) {
	extract( shortcode_atts( array(
		'id' => '0'
	), $atts ) );

        $song = new Song;
	$artist = new Artist;

        $html = "<a href='$song->url'>" .$artist->loadById($song->loadById(esc_attr($id))->artist_id)->name . " - ". $song->name. "</a>";

	unset($artist);
        unset($song);
        return $html;
    }

    public function __construct() {
        GLOBAL $wpdb, $TABLE_NAME;

        self::$songTable = $wpdb->prefix . $TABLE_NAME[TABLE_SONGS];

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

            $this->poster_id = $this->query_result->poster_id;
            $this->last_updated_by_id = $this->query_result->last_updated_by_id;
            $this->create_date = $this->query_result->create_date;
            $this->update_date = $this->query_result->update_date;

	    $this->artist_id = $this->query_result->artist_id;
            $this->name = $this->query_result->name;
            $this->url = $this->query_result->url;
	    $this->price = $this->query_result->price;
        } else {
            $this->query_result = 

            $this->id = 
            $this->poster_id = 
            $this->last_updated_by_id = 
            $this->create_date = 
            $this->update_date = 

	    $this->artist_id;
            $this->name = 
            $this->url = 
	    $this->price = 0;
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
                        FROM " .self::$songTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadByPrice ($price) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM " .self::$songTable. "
                        WHERE price = %u", $price);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAll ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$songTable. "
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function deleteById ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare(
                       "DELETE FROM " .self::$songTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        }
        return $this->getTotalRows();
    }

     // update artist entry
    public function updateById ($song_id, $artist_id, $song_name, $url, $price) {
        GLOBAL $wpdb, $i18n_domain;
        GLOBAL $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                 "UPDATE " .self::$songTable. "
                  SET update_date = now(),
		      artist_id = %u,
                      name = %s,
                      url = %s,
		      price = %s,
                      last_updated_by_id = %u
                  WHERE id = %s",
                  $artist_id, $song_name, $url, $price, $current_user->ID, $song_id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) {
            wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );
        } else {
             // was entered successfully into database
            return $this->getTotalRows();
        }
    }

    public function insert ($artist_id, $song_name, $url, $price) {
        GLOBAL $wpdb, $i18n_domain;
        GLOBAL $current_user;

        get_currentuserinfo();

        $this->query = $wpdb->prepare(
                       "INSERT INTO " .self::$songTable. "
                        (create_date, update_date, poster_id, last_updated_by_id, artist_id, name, url, price)
                        VALUES (now(), now(), %u, %u, %s, %s, %s, %s)",
                        $current_user->ID, $current_user->ID, $artist_id, $song_name, $url, $price);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === 0 OR $this->getTotalRows() === FALSE) {
            return sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query); 
        } else {
             // was entered successfully into database
            return 1;
        }
    }
}  /* end class Song */

?>