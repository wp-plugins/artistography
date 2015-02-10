<?php
add_shortcode( 'artistography_show_cart', 'Sale::shortCodeShowCart' );
add_shortcode( 'artistography_show_checkout', 'Sale::shortCodeShowCheckout' );

class Sale
{

	public function __construct() {
		GLOBAL $wpdb, $TABLE_NAME;
	}

	public function __destruct() {
		 /* Just in case we need it */
	}

	public static function shortCodeShowCart( $atts, $content=null, $code="" ) {
		$html = "Cart";
		return $html;
	}

	public static function shortCodeShowCheckout( $atts, $content=null, $code="" ) {
                $html = "Checkout";
                return $html;
        }
} /* end class Sales */
?>
