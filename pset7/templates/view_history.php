<?
if($results !== FALSE):
?>
    <table class="table table-bordered table-hover">
        <tr>
            <th>Date</th>
            <th>Transaction Type</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
        <tbody class="table-striped">
<?
    foreach($results as $transaction){
        extract($transaction);
        print("<tr>");
        print("<td>".date("r",$date)."</td>");
        print("<td>{$type}</td>");
        print("<td>{$symbol}</td>");
        print("<td>{$shares}</td>");
        print("<td>".numberFormat($price)."</td>");
        print("</tr>");
    }
    print("</tbody>");
    print("</table>");
    endif;
?>