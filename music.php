<?php
$servername = "localhost";
$username = "y23_2A_Meixner";
$password = "test";
$dbname = "y23_2A_Meixner";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
  die("Verbindung fehlgeschlagen: " . $conn->connect_error);
}

function insertEntry($artist, $album, $published, $format) {
  global $conn;
  $stmt = $conn->prepare("INSERT INTO music_collection (artist, album, published, format) VALUES (?, ?, ?, ?)");
  if ($stmt === false) {
    die("Fehler bei der Vorbereitung der Anweisung: " . $conn->error);
  }
  $stmt->bind_param("ssss", htmlspecialchars($artist), htmlspecialchars($album), htmlspecialchars($published), htmlspecialchars($format));
  $stmt->execute();
  $stmt->close();
}

function deleteEntry($id) {
  global $conn;
  $stmt = $conn->prepare("DELETE FROM music_collection WHERE id = ?");
  if ($stmt === false) {
    die("Fehler bei der Vorbereitung der Anweisung: " . $conn->error);
  }
  $stmt->bind_param("i", htmlspecialchars($id));
  $stmt->execute();
  $stmt->close();
}

function displayEntries() {
  global $conn;
  $result = $conn->query("SELECT id, artist, album, published, format FROM music_collection");
  if ($result === false) {
    echo "Fehler bei der Abfrage: " . $conn->error;
  } else {
    while($row = $result->fetch_assoc()) {
      echo "<tr><td>".htmlspecialchars($row["artist"])."</td><td>".htmlspecialchars($row["album"])."</td><td>".htmlspecialchars($row["published"])."</td><td>".htmlspecialchars($row["format"])."</td><td><form method='post' action='music.php'><input type='hidden' name='delete_id' value='".htmlspecialchars($row["id"])."'><input type='submit' value='Löschen' class='delete-button'></form></td></tr>";
    }
  }
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  if (isset($_POST['delete_id'])) {
    deleteEntry($_POST['delete_id']);
  } else {
    insertEntry($_POST['artist'], $_POST['album'], $_POST['published'], $_POST['format']);
  }
}
?>

<!DOCTYPE html>
<html>
<head>
  <title>Musiksammlung</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #fff;
      color: #000;
      padding: 20px;
    }
    form {
      background-color: #fff;
      padding: 20px;
      border-radius: 5px;
      margin-bottom: 20px;
      max-width: 600px;
      margin: 20px auto;
      border: 1px solid #000;
      box-shadow: 0px 0px 10px 0px(0, 0, 0, 0.1);
    }
    input[type="text"], input[type="date"], select {
      width: calc(100% - 20px);
      padding: 10px;
      margin-bottom: 10px;
      border-radius: 5px;
      border: 1px solid #000;
      background-color: #fff;
      color: #000;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }
    input[type="submit"] {
      background-color: #007BFF;
      color: #fff;
      border: none;
      border-radius: 5px;
      padding: 10px 20px;
      cursor: pointer;
      display: block;
      margin: 20px auto;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      transition: background-color 0.3s ease;
    }
    input[type="submit"]:hover {
      background-color: #000;
    }
    table {
      width: 100%;
      border-collapse: collapse;
      color: #000;
      max-width: 800px;
      margin: 0 auto;
      border: 1px solid #000;
      box-shadow: 0px 0px 10px 0px rgba(0, 0, 0, 0.1);
    }
    th, td {
      padding: 10px;
      text-align: left;
      border-bottom: 1px solid #ddd;
    }
    th {
      border-bottom: 2px solid #000;
    }
    .delete-button {
      background-color: #f44336;
      color: #fff;
      border: none;
      border-radius: 5px;
      padding: 5px 10px;
      cursor: pointer;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      transition: background-color 0.3s ease;
    }
    .delete-button:hover {
      background-color: #e53935;
    }
  </style>
</head>
<body>
  <form method="post" action="music.php">
    Künstler: <input type="text" name="artist" required><br>
    Album: <input type="text" name="album" required><br>
    Veröffentlicht am: <input type="date" name="published" required><br>
    Format: <select name="format" required>
      <option value="c">CD</option>
      <option value="k">Kassette</option>
      <option value="v">Vinyl</option>
      <option value="d">Digital</option>
    </select><br>
    <input type="submit" value="Neu erstellen">
  </form>
  <table>
    <tr>
      <th>Künstler</th>
      <th>Album</th>
      <th>Erscheinungsjahr</th>
      <th>Format</th>
      <th></th>
    </tr>
    <?php displayEntries(); ?>
  </table>
</body>
</html>

<?php
$conn->close();
?>