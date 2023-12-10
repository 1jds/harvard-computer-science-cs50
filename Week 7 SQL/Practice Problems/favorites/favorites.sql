-- These are the commands I used for this practice:

-- to see the schema for how the database was created. The schema was as above following .schema
.schema
CREATE TABLE shows (id INTEGER, title TEXT NOT NULL, PRIMARY KEY(id));
CREATE TABLE genres (show_id INTEGER, genre TEXT NOT NULL, FOREIGN KEY(show_id) REFERENCES shows(id));

-- to see the full list of shows
SELECT * FROM shows;

-- to practice updating only one row
UPDATE shows SET title = "How I Met Your Mother" WHERE title = "How i met your mother";

-- to see the update in effect; could have done this more selectively!
SELECT * FROM shows;

-- to see what different versions of the title "Avatar: The Last Airbender" there were in the data
-- This selects everything from the table shows where the row value for the title column has a value of "Avatar" followed by any number of wildcard characters
SELECT * FROM shows WHERE title LIKE "Avatar%";

-- The resulting table is as follows:
-- +-----+----------------------------+
-- | id  |           title            |
-- +-----+----------------------------+
-- | 20  | Avatar: The Last Airbender |
-- | 29  | Avatar The Last Airbender  |
-- | 34  | Avatar The Last Airbender  |
-- | 36  | Avatar the Last Airbender  |
-- | 51  | Avatar the Last Airbender  |
-- | 101 | Avatar: The Last Airbender |
-- | 123 | Avatar                     |
-- | 149 | Avatar: The Last Airbender |
-- | 150 | Avatar the Last Airbender  |
-- +-----+----------------------------+
-- I'm not 100% sure of the title that's just "Avatar", but I'm assuming that these all refer to the same move. So we can do the following to rationalise them:
UPDATE shows SET title = "Avatar: The Last Airbender" WHERE title LIKE "Avatar%";

-- If we then re-run our previous command, we get the following table:
-- (Previous command was: SELECT * FROM shows WHERE title LIKE "Avatar%";)
-- +-----+----------------------------+
-- | id  |           title            |
-- +-----+----------------------------+
-- | 20  | Avatar: The Last Airbender |
-- | 29  | Avatar: The Last Airbender |
-- | 34  | Avatar: The Last Airbender |
-- | 36  | Avatar: The Last Airbender |
-- | 51  | Avatar: The Last Airbender |
-- | 101 | Avatar: The Last Airbender |
-- | 123 | Avatar: The Last Airbender |
-- | 149 | Avatar: The Last Airbender |
-- | 150 | Avatar: The Last Airbender |
-- +-----+----------------------------+
-- At this point, you're probably wondering (at least I am!) why we don't combine these into one row... but the instructions don't say to do that...

-- I'm going to put these into alphabetical order to get some of the similar but divergent movie titles closer together
-- Interestingly, this puts capital 'A' titles before lower-case 'a' titles... I didn't know that would happen!
SELECT * FROM shows ORDER BY title;

--  OK, let's run through some more fixes (I will just put the fixes below)
UPDATE shows SET title = "Arrow" WHERE title = "arrow";
-- This one was interesting. It didn't work with LIKE with or without an apostrophe. Not sure if the apostrophe was too much for it
UPDATE shows SET title = "It's Always Sunny In Philadelphia" WHERE title = "Its Always Sunny in Philidelphia";
-- This one uses LIKE with a wild-card %
 UPDATE shows SET title = "Parks And Recreation" WHERE title LIKE "Parks And Rec%";
--  To correct "Thevoffice", I used the following:
UPDATE shows SET title = "The Office" WHERE title LIKE "The_Office";
-- There were some other ones which required escaping apostrophes and what not. At one point, I updated "Grey's Anatomy" based on the ID value.

