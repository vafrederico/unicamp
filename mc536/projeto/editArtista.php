<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
		$client = new Client();

	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1))
		header('Location: login.php');

		error_reporting(E_ALL);
		
	
	if(isset($_POST['uri'])){
		$run = "" . 
"MATCH (n:Person)-[r:LIKES]->(m:Artista) " .
"WHERE n.usuario='{$_SESSION['usuario']}' " .
"AND m.uri='{$_POST['uri']}' " .
"SET r.rating = {$_POST['rating']} " .
"return n, m";
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        header('Location: artistas.php');

	}
			$run = "" . 
"MATCH (n:Person)-[r:LIKES]->(m:Artista) " .
"WHERE n.usuario='{$_SESSION['usuario']}' " .
"AND m.uri='{$_GET['uri']}' " .
"return r.rating";
$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        foreach($result as $row) {
        	$rating =  $row->offsetGet('r.rating');
        }
?>
<form method="POST">
	<input type='hidden' name='uri' value=<?php echo $_GET['uri'];?>><br>
	Nota: <select name='rating'>
	<option value='1' <?php if($rating == 1) echo "selected"; ?>>1</option>
	<option value='2' <?php if($rating == 2) echo "selected"; ?>>2</option>
	<option value='3' <?php if($rating == 3) echo "selected"; ?>>3</option>
	<option value='4' <?php if($rating == 4) echo "selected"; ?>>4</option>
	<option value='5' <?php if($rating == 5) echo "selected"; ?>>5</option>
</select>
	<br>
	<input type='submit'>
</form>