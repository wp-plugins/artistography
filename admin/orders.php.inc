<?php

GLOBAL $wpdb, $i18n_domain, $TABLE_NAME;

$orders = new Orders;
$i = 0;

echo "<table>
	<thead>
		<th>#</td>
		<th>Forename</th>
		<th>Surname</th>
		<th>Email</th>
		<th>Address</th>
		<th>Products purchased</th>
		<th>Payment Status</th>
		<th>Amount</th>
		<th>Currency</th>
		<th>Item Name</th>
		<th>Item Number</th>
		<th>User ID</th>
	</thead>
	<tbody>";
	if ($orders->getTotalRows() > 0) {
		do {
		$products = unserialize($orders->itemsOrdered);
		echo "	<tr>
				<td>$orders->id</td>
				<td>$orders->forename</td>
				<td>$orders->surname</td>
				<td>$orders->email</td>
				<td>$orders->address_line_1, $orders->postcode, $orders->town</td>
				<td>";
		echo "			<ol>";
		for($j = 0; $j < count($products); $j++) {
			echo "			<li>" .$products[$j]. "</li>";
		}
		echo "			</ol>";
		echo	"	</td>
				<td>$orders->payment_status</td>
				<td>$orders->payment_amount</td>
				<td>$orders->payment_currency</td>
				<td>$orders->item_name</td>
				<td>$orders->item_number</td>
				<td>$orders->user_id</td>
			</tr>";
		$orders->getNodeNext();
		$i++;
		} while($i<$orders->getTotalRows());
	} else {
		echo "<tr><td colspan='9'>There are no orders yet.</td></tr>";
	}
echo "	</tbody>
</table>";

?>
