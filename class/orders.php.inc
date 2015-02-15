<?php
add_shortcode( 'artistography_show_cart', 'Orders::shortCodeShowCart' );
add_shortcode( 'artistography_show_checkout', 'Orders::shortCodeShowCheckout' );
add_shortcode( 'artistography_show_thankyou', 'Orders::shortCodeShowThankyou' );
add_shortcode( 'artistography_show_orders', 'Orders::shortCodeShowOrders' );
add_shortcode( 'artistography_ipn', 'Orders::shortCodeIPN' );
class Orders
{
	protected static $ordersTable = NULL;  // TABLE NAME of MUSIC ALBUM TABLE

	public $album_id = NULL;
	public $album = NULL;

	public $id = NULL;

	public $forename = NULL;
        public $surname = NULL;
        public $email = NULL;
        public $address_line_1 = NULL;
        public $postcode = NULL;
        public $town = NULL;
        public $itemsOrdered = NULL;
        public $created = NULL;
        public $txn_id = NULL;
	public $custom = NULL;
        public $user_ip = NULL;
	public $user_id = NULL;

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

		self::$ordersTable = $wpdb->prefix . $TABLE_NAME[TABLE_ARTIST_ORDERS];

		$this->loadAll();
	}

	public function __destruct() {
		 /* Just in case we need it */
	}

	protected function &loadCurrNodeValues () {
        	GLOBAL $wpdb, $_SERVER;

        	if ($this->getTotalRows() > 0) {
            		$this->query_result = $wpdb->get_row($this->query, OBJECT, $this->getCurrNode());

			 // meta data info update
			$this->id = $this->query_result->id;
			$this->forename = $this->query_result->forename;
			$this->surname = $this->query_result->surname;
			$this->email = $this->query_result->email;
			$this->album_line_1 = $this->query_result->address_line_1;
			$this->postcode = $this->query_result->postcode;
			$this->town = $this->query_result->town;

			$this->itemsOrdered = $this->query_result->itemsOrdered;
			$this->created = $this->query_result->created;
			$this->txn_id = $this->query_result->txn_id;
			$this->user_id = $this->query_result->user_id;
			$this->user_ip = $this->query_result->user_ip;
		} else {
			$this->query_result =
            
			$this->album_id =
			$this->album =

			$this->id =
			$this->forename =          
			$this->surname =
			$this->email =
			$this->address_line_1 =
			$this->postcode =   
			$this->town =       

			$this->itemsOrdered =
			$this->created =
			$this->txn_id =
			$this->custom =
			$this->user_ip = 
			$this->user_id = 0;
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
                        FROM " .self::$ordersTable. "
                        WHERE id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadByUserId ($id) {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = $wpdb->prepare("SELECT *
                        FROM " .self::$ordersTable. "
                        WHERE user_id = %u", $id);
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

    public function &loadAll ($order_by = 'id') {
        GLOBAL $wpdb, $i18n_domain;

        $this->query = "SELECT *
                        FROM " .self::$ordersTable. "
                        ORDER BY $order_by";
        $this->setTotalRows($wpdb->query($this->query));

        if ($this->getTotalRows() === FALSE) wp_die( sprintf(__('An error occurred while trying to perform a query: "%s"', $i18n_domain), $this->query) );

        $this->setCurrNode(0); // set to first node
        return $this->loadCurrNodeValues();
    }

	public function locateOrderMusicDownloadId($music_id) {
		GLOBAL $wpdb, $i18n_domain;

		$Music = new Music;
		$Music->loadById($music_id);
		$item_name = $Music->id .' - '. $Music->artist_name .' - '. $Music->album_name;
		
		$found = false;
		$i = 0;
		
        	if ($this->getTotalRows() > 0) {
                	do {
                		$products = unserialize($this->itemsOrdered);
                		for($j = 0; $j < count($products); $j++) {
					$product_id = str_replace('album_download_', '', explode(' - ', $products[$j])[0]);
                        		if (strcmp($music_id, $product_id) == 0) {
						$found = true;
					}
                		}
                		$orders->getNodeNext();
                		$i++;
        	        } while($i<$orders->getTotalRows());
	        } else {
			$found = false;
		}

		return $found;
	}

	public static function shortCodeShowCart( $atts, $content=null, $code="" ) {
		GLOBAL $i18n_domain;

		 /*** Process Cart Actions ***/
		if ($_POST['artistography_product_id']) {
			$product_id = $_POST['artistography_product_id'];
			$qty = $_POST['artistography_qty'];
			$action = $_POST['artistography_action'];
			switch($action) {
				case "add":
					$_SESSION['artistography_cart'][$product_id] = $_SESSION['artistography_cart'][$product_id] + $qty;
				break;
				case "empty":
					unset($_SESSION['artistography_cart']);
				break;
				case "remove":
					unset($_SESSION['artistography_cart'][$product_id]);
				break;
			}
		}

		 /*** Display Cart Contents ***/
		$html = self::showCart();
		return $html;
	}

	public static function shortCodeShowCheckout( $atts, $content=null, $code="" ) {
		GLOBAL $i18n_domain, $buynow_icon_url, $buynow_icon_width, $buynow_icon_height;
		$html = '';

		$album = new Music;
		$sandbox = get_option('wp_artistography_paypal_sandbox');

		if(!is_user_logged_in()) {
			$html .= "In order to buy you must first register or be logged into our website that way we can keep track of your orders, and you can return to download your files again at a later time if you lose them.<br/>\n";
			$html .= "<div>Existing Users:<br/>\n";
			$html .= wp_login_form(array('echo' => false));
			$html .= "<a href=\"" .wp_lostpassword_url( get_permalink() ). "\" title=\"Lost Password\">Lost Password</a>";
			$html .= " | New Users: <a href=\"" .wp_registration_url(). "\" target='_blank'>Register</a>";
			$html .= "</div>\n";
		} else {
			$result = self::showInvoice();
			if(!$result) {
				$html .= "<font style='font-size:14pt'>The shopping cart is empty.</font>";
			} else {
				$html .= "Welcome, " .wp_get_current_user()->user_login. "!";
				$html .= $result;

				if($sandbox) {
				  $html .= "<form action='https://www.sandbox.paypal.com/cgi-bin/webscr' method='post' class='standard-form'>";
				} else {
				  $html .= "<form action='https://www.paypal.com/cgi-bin/webscr' method='post' class='standard-form'>";
				}
				$i = 1;
				foreach($_SESSION['artistography_cart'] as $product => $qty) {
				  $album->loadById($product);
				  $html .= "<input type='hidden' name='item_name_$i' value='album_download_$album->id - $album->artist_name - $album->album_name' />";
				  $html .= "<input type='hidden' name='quantity_$i' value='$qty' />";
				  $html .= "<input type='hidden' name='amount_$i' value='$album->price' />";
				  $i++;
				}
				$html .= "<input type='hidden' name='cmd' value='_cart' />
					  <input type='hidden' name='upload' value='1' />
					  <input type='hidden' name='business' value='" .get_option('wp_artistography_donate_email'). "' />";

				$html .= "<input type='hidden' name='custom' value='user_id=" .get_current_user_id(). "' />";
				$html .= "<input type='hidden' name='currency_code' value='USD' />\n";
                                $html .= "<input type='hidden' name='lc' value='US' />\n";
                                $html .= "<input type='hidden' name='rm' value='2' />\n";
                                $html .= "<input type='hidden' name='return' value='" .get_permalink(get_option('wp_artistography_thankyou_page')). "' />\n";
                                $html .= "<input type='hidden' name='cancel_return' value='" .get_permalink(get_option('wp_artistography_cart_page')). "' />\n";
                                $html .= "<input type='hidden' name='notify_url' value='" .get_permalink(get_option('wp_artistography_ipn_page')). "' />\n";

                		$html .= "  <div align='right'><input type='submit' value=''
						style='border:none;
						       width: " .$buynow_icon_width. "px; height: " .$buynow_icon_height. "px;
				              	       background:url($buynow_icon_url) no-repeat;
					               background-size:" .$buynow_icon_width. "px " .$buynow_icon_height. "px;' align='right' /></div>";
				$html .= "</form>";
			}
		}
                return $html;
        }

        public static function shortCodeShowThankyou( $atts, $content=null, $code="" ) {
                GLOBAL $i18n_domain;
		$html = "";

		 /* empty the cart */
		session_destroy();

                $html .= "Thank you for completing your order with us.  To see all of your completed orders please click <a href='" .SITEURL. "/artistography_orders'>here</a>.<br/><br/>";
		$html .= "";
                return $html;
        }

        public static function shortCodeShowOrders( $atts, $content=null, $code="" ) {
                GLOBAL $i18n_domain;

                $html = "";
                return $html;
        }

         // IPN Guide: https://www.paypalobjects.com/webstatic/en_US/developer/docs/pdf/ipnguide.pdf
         //http://code.tutsplus.com/tutorials/wordpress-and-paypal-an-introduction--wp-25074
        public static function shortCodeIPN( $atts, $content=null, $code="" ) {
                GLOBAL $i18n_domain, $TABLE_NAME;
                $html = "";

		$header = "";
		$req = 'cmd=_notify-validate';
		foreach($_POST as $key => $value) {
			$value = urlencode(stripslashes($value));
			$req .= "&$key=$value";
		}
		$header .= "POST /cgi-bin/webscr HTTP/1.0\r\n";
		$header .= "Content-Type: application/x-www-form-urlencoded\r\n";
		$header .= "Content-Length: " .strlen($req). "\r\n\r\n";
		$fp = fsockopen('ssl://www.sandbox.paypal.com', 443, $errno, $errstr, 30);

		if (!$fp) {
			// http error
		} else {
			fputs ($fp, $header . $req);
			while(!feof($fp)) {
				$res = fgets($fp, 1024);

				$fh = fopen('results.txt', 'w');
					fwrite($fh, $req);
					fwrite($fh, $res);
					fclose($fh);

				if (strcmp($res, "VERIFIED") == 0) {
					$firstName	= $_POST['first_name'];
					$lastName	= $_POST['last_name'];
					$payerEmail	= $_POST['payer_email'];
					$addressStreet	= $_POST['address_street'];
					$addressZip	= $_POST['address_zip'];
					$addressCity	= $_POST['address_city'];
					$productsBought	= $_POST[''];
					$txnID		= $_POST['txn_id'];

        	                        $this->custom = array();
	                                parse_str($txn_id->custom, $this->custom);
					$userID = $this->custom['user_id'];

					 //Used to store quickly items bought
					$i = 1;
					foreach($_POST as $key => $value) {
						if($key == 'item_name'.$i) {
							$products_bought[] = $value;
							$i++;
						}
					}
					$products = serialize($products_bought);

					$wpdb->insert(self::$ordersTable,
					array(	'forename'		=> $firstName,
						'surname'		=> $lastName,
						'email'			=> $payerEmail,
						'address_line_1'	=> $addressStreet,
						'postcode'		=> $addressZip,
						'town'			=> $addressCity,
						'itemsOrdered'		=> $products,
						'created'		=> current_time('mysql'),
						'txn_id'		=> $txnID,
						'user_ip'		=> $_SERVER['REMOTE_ADDR'],
						'user_id'		=> $userID
					),
					array(	'%s',			// FORENAME
						'%s',			// SURNAME
						'%s',			// EMAIL
						'%s',			// ADDRESS 1
						'%s',			// PCODE
						'%s',			// TOWN
						'%s',			// ORDERED
						'%s',			// STATUS
						'%s',			// CREATED
						'%s',			// USER IP
						'%s'			// WORDPRESS USER ID
					));
				} else if (strcmp($res, "INVALID") == 0) {
					// You may prefer to store the transaction even if fail
				} /* end if */
			} /* end while */
			fclose($fp);
		} /* end if */

                return $html;
        }

	public function showCart() {
		GLOBAL $i18n_domain, $checkout_icon_url, $checkout_icon_width, $checkout_icon_height;

                $order = new Orders;
                $album = new Music;

                $total = (float)"0.00";

		 /*** Display Cart Contents ***/
                if(!empty($_SESSION['artistography_cart'])) {
                  foreach($_SESSION['artistography_cart'] as $product => $qty) {
		    if(strpos($product, 'album_download_') !== FALSE) {
			$album_download = true;
			$product_id = str_replace('album_download_', '', $product);
		    }
                    $album->loadById($product_id);
                    $total += ($qty * (float)($album->price));
                    $html = "<center><table>
                             <tr>
                                <th>" .__("Quanity", $i18n_domain). "</th>
                                <th>" .__("Item", $i18n_domain). "</th>
                                <th>" .__("Price", $i18n_domain). "</th>
                                <th>" .__("Action", $i18n_domain). "</th>
                             </tr>
                             <tr>
                                <td>$qty</td>
                                <td><img src='" .stripslashes($album->picture_url). "' width='50' height='50' />
                                        $album->artist_name - $album->album_name
                                </td>
                                <td>" .CURRENCY. "$album->price</td>
                                <td>
                                  <form action='' method='post'>
                                    <input type='hidden' name='artistography_product_id' value='$product' />
                                    <input type='hidden' name='artistography_action' value='remove' />
                                    <input type='submit' value='Remove' />
                                  </form>
                                </td>
                             </tr>";
                  }
                $html .= "<tr>
                                <td colspan='2'>Total:</td><td>" .CURRENCY.number_format(round($total, 2), 2). "</td><td></td>
                             </tr>
                             </table></center><br/>\n
                                <a href='" .SITEURL. "/artistography_checkout'><img src='$checkout_icon_url' width='$checkout_icon_width' height='$checkout_icon_height' style='border:0px;' align='right' /></a>";
                } else {
                  $html = "<font style='font-size:14pt'>The shopping cart is empty.</font>";
                }
                return $html;
	}

	public function showInvoice() {
		GLOBAL $i18n_domain;

		$order = new Orders;
                $album = new Music;
                $total = (float)"0.00";

                 /*** Display Cart Contents ***/
                if(!empty($_SESSION['artistography_cart'])) {
                  foreach($_SESSION['artistography_cart'] as $product => $qty) {
                    $album->loadById($product);
                    $total += ($qty * (float)($album->price));
                    $html = "<center><table>
                             <tr>
                                <th>" .__("Quanity", $i18n_domain). "</th>
                                <th>" .__("Item", $i18n_domain). "</th>
                                <th>" .__("Price", $i18n_domain). "</th>
                             </tr>
                             <tr>
                                <td>$qty</td>
                                <td><img src='" .stripslashes($album->picture_url). "' width='50' height='50' />
                                        $album->artist_name - $album->album_name
                                </td>
                                <td>" .CURRENCY. "$album->price</td>
                             </tr>";
                  }
                $html .= "<tr>
                                <td colspan='2'>Total:</td><td>" .CURRENCY.number_format(round($total, 2), 2). "</td>
                             </tr>
                             </table></center><br/>\n
                                <a href='" .SITEURL. "/artistography_checkout'><img src='$checkout_icon_url' width='$checkout_icon_width' height='$checkout_icon_height' style='border:0px;' align='right' /></a>";
                } else {
		  return false;
                }
                return $html;
	}
} /* end class Sales */
?>
