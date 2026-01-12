#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <cstdio>
#include <sstream>
#include <cstdlib> // for system("clear");
// for timer
#include <chrono>
#include <thread>
#include <set>


using namespace std;
namespace fs = std :: filesystem;
// global vector 
vector<string> SavedRecipes;

// string manipulate (string s);
void ListAll();

struct RecipeStructure{
    string name;
    vector<string> ingredients;
    vector<string> steps;
};

struct AllRecipes{
    vector<RecipeStructure> Recipe;
};
//global object for AllRecipes
AllRecipes Rec;

struct MatchedRecipe{
    string Mname;
    int matched_per;
};

struct A_M_R{
    vector<MatchedRecipe> M_Rec;
};

string manipulate(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    return s;
}

void LoadRecipes(){
    Rec.Recipe.clear();
    
    
    // loading all recipes 
    int i=0;
    for (const auto list : fs::directory_iterator(".")){
        if(list.path().extension()==".txt"){
            RecipeStructure r;
            //saving recipe names each iteration
            r.name=list.path().filename().replace_extension();
            Rec.Recipe.push_back(r);

            //creating a file for just reading
            string line;
            ifstream file(r.name+ ".txt");
            if(!file){
                cerr << "Error! opening file\n";
            }
            getline(file , line); getline(file , line); getline(file , line);
            line = line.substr(13);
            istringstream iss(line);
        // saving all ingredients of a recipe each iteration
            while(getline(iss, line, ',')){
                
                Rec.Recipe[i].ingredients.push_back(line);
                
            }

         //saving all steps of a recipe each iteration
            int j=1;
            
            while (getline(file, line)) {

                if (line.empty()) continue;   // skip blank lines

                // safety check before substr
                if (line.size() < 8) continue;

                if (j >= 10 && line.size() > 9)
                    line = line.substr(9);
                else if (line.size() > 8)
                    line = line.substr(8);

                Rec.Recipe[i].steps.push_back(line);
                j++;
            }

            i++;
            file.close();
        }
    }
    
}

void loadRecipeName(){
    SavedRecipes.clear();
    for( const auto R_list : fs::directory_iterator(".")){
        if(R_list.path().extension()==".txt"){
            SavedRecipes.push_back(R_list.path().filename().replace_extension());
        }
    }

}


void CreateBuiltInRecipes() {

    struct BuiltInRecipe {
        string name;
        vector<string> ingredients;
        vector<string> steps;
    };

    vector<BuiltInRecipe> recipes = {

        {
            "Chicken Karahi",
            {"chicken","tomatoes","ginger","garlic","green chillies","oil","salt","red chilli powder"},
            {
                "Heat oil in a karahi over medium heat. Add ginger and garlic and sauté for 1 minute until fragrant",
                "Add chicken pieces and cook for 10 minutes, stirring until the chicken changes color",
                "Add tomatoes, salt, and red chilli powder and cook for 15 minutes until oil separates",
                "Add green chillies and cook on low heat for 5 minutes",
                "Serve hot with naan or roti"
            }
        },

        {
            "Chicken Biryani",
            {"chicken","rice","onion","tomatoes","yogurt","biryani masala","ginger","garlic","oil","salt"},
            {
                "Fry sliced onions in oil until golden brown and remove half for garnishing",
                "Add ginger garlic paste and chicken and cook for 15 minutes until tender",
                "Add tomatoes, yogurt, biryani masala, and salt and cook for 10 minutes",
                "Layer partially cooked rice over chicken mixture",
                "Cover and steam on low heat for 20 minutes"
            }
        },

        {
            "Beef Nihari",
            {"beef","nihari masala","ginger","garlic","oil","salt","water","wheat flour"},
            {
                "Heat oil and fry ginger and garlic for 1 minute",
                "Add beef and cook for 15 minutes until lightly browned",
                "Add water, salt, and nihari masala and simmer for 120 minutes",
                "Mix flour with water and add to thicken gravy",
                "Cook for another 10 minutes and serve hot"
            }
        },

        {
            "Haleem",
            {"wheat","lentils","beef","ginger","garlic","oil","salt","haleem masala"},
            {
                "Boil wheat, lentils, and beef together for 120 minutes until very soft",
                "Blend the mixture to a smooth consistency",
                "Heat oil and add haleem masala",
                "Add blended mixture and cook for 30 minutes",
                "Serve hot with garnish"
            }
        },

        {
            "Aloo Keema",
            {"minced beef","potatoes","onion","tomatoes","ginger","garlic","oil","salt","spices"},
            {
                "Heat oil and fry onions until golden",
                "Add ginger garlic paste and minced beef and cook for 10 minutes",
                "Add tomatoes and spices and cook for 15 minutes",
                "Add potatoes and simmer for 20 minutes",
                "Serve hot with roti"
            }
        },

        {
            "Daal Chawal",
            {"lentils","rice","onion","garlic","oil","salt","turmeric"},
            {
                "Boil lentils with turmeric and salt for 25 minutes",
                "Heat oil and fry onion and garlic for 5 minutes",
                "Add tarka to lentils and mix well",
                "Cook rice separately until fluffy",
                "Serve daal with rice"
            }
        },

        {
            "Chapli Kabab",
            {"minced beef","onion","tomatoes","green chillies","spices","oil","salt"},
            {
                "Mix minced beef with onions, tomatoes, spices, and salt",
                "Shape mixture into flat kababs",
                "Heat oil in pan and shallow fry kababs",
                "Cook each side for 4 minutes until crispy",
                "Serve hot with chutney"
            }
        },

        {
            "Chicken Qorma",
            {"chicken","onion","yogurt","ginger","garlic","oil","salt","qorma masala"},
            {
                "Fry onions until golden brown",
                "Add ginger garlic paste and chicken and cook for 10 minutes",
                "Add yogurt and qorma masala and cook for 15 minutes",
                "Cover and simmer on low heat for 20 minutes",
                "Serve hot with naan"
            }
        },

        {
            "Seekh Kabab",
            {"minced beef","ginger","garlic","green chillies","spices","oil","salt"},
            {
                "Mix minced beef with spices, ginger, and garlic",
                "Shape mixture onto skewers",
                "Grill or pan fry kababs",
                "Cook for 10 minutes turning sides",
                "Serve hot with chutney"
            }
        },

        {
            "Chicken Pulao",
            {"chicken","rice","onion","garlic","ginger","oil","salt","whole spices"},
            {
                "Fry onions in oil until golden",
                "Add ginger garlic and chicken and cook for 10 minutes",
                "Add water and whole spices and bring to boil",
                "Add rice and cook until water dries",
                "Cover and steam for 15 minutes"
            }
        },

        {
            "Anda Curry",
            {"eggs","onion","tomatoes","ginger","garlic","oil","salt","spices"},
            {
                "Boil eggs and peel shells",
                "Fry onions in oil until golden",
                "Add tomatoes and spices and cook for 10 minutes",
                "Add boiled eggs and simmer for 10 minutes",
                "Serve hot"
            }
        },

        {
            "Sabzi",
            {"mixed vegetables","onion","tomatoes","oil","salt","spices"},
            {
                "Heat oil and fry onions until soft",
                "Add tomatoes and spices and cook for 10 minutes",
                "Add vegetables and mix well",
                "Cover and cook for 20 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Tikka",
            {"chicken","yogurt","spices","lemon","salt","oil"},
            {
                "Marinate chicken with yogurt and spices for 60 minutes",
                "Preheat grill or pan",
                "Cook chicken for 15 minutes turning sides",
                "Brush oil during cooking",
                "Serve hot with salad"
            }
        },

        {
            "Beef Pulao",
            {"beef","rice","onion","oil","salt","whole spices"},
            {
                "Fry onions until golden",
                "Add beef and cook for 20 minutes",
                "Add water and whole spices and simmer until beef is tender",
                "Add rice and cook until water dries",
                "Steam for 15 minutes"
            }
        },

        {
            "Kadhi Pakora",
            {"yogurt","besan","onion","spices","oil","salt"},
            {
                "Prepare pakoras and fry until golden",
                "Mix yogurt and besan with spices",
                "Cook kadhi on low heat for 30 minutes",
                "Add pakoras and simmer for 10 minutes",
                "Serve hot with rice"
            }
        },
        {
            "Chicken Pakora",
            {"chicken","besan","ginger","garlic","spices","oil","salt"},
            {
                "Mix chicken pieces with besan, ginger garlic paste, spices, and salt",
                "Heat oil in a deep pan over medium heat",
                "Carefully drop coated chicken pieces into hot oil",
                "Fry for 6 to 8 minutes until golden and crispy",
                "Remove and serve hot with chutney"
            }
        },

        {
            "Beef Paya",
            {"beef trotters","onion","ginger","garlic","oil","salt","spices"},
            {
                "Heat oil and fry onions until golden brown",
                "Add ginger garlic paste and spices and cook for 2 minutes",
                "Add beef paya and water and bring to boil",
                "Cover and cook on low heat for 180 minutes until tender",
                "Serve hot with naan"
            }
        },

        {
            "Chicken Shami Kabab",
            {"chicken","chana daal","onion","ginger","garlic","spices","oil","salt"},
            {
                "Boil chicken and lentils together until soft",
                "Grind mixture with spices into a thick paste",
                "Shape into kababs",
                "Shallow fry each side for 3 minutes until golden",
                "Serve hot"
            }
        },

        {
            "Beef Seekh Kabab",
            {"minced beef","ginger","garlic","green chillies","spices","oil","salt"},
            {
                "Mix minced beef with spices and aromatics",
                "Shape mixture onto skewers",
                "Heat oil or grill pan",
                "Cook kababs for 10 minutes turning sides",
                "Serve hot with salad"
            }
        },

        {
            "Chicken Kofta",
            {"minced chicken","onion","tomatoes","ginger","garlic","oil","salt","spices"},
            {
                "Shape minced chicken into small balls",
                "Heat oil and fry onions until golden",
                "Add tomatoes and spices and cook for 10 minutes",
                "Add koftas carefully and simmer for 20 minutes",
                "Serve hot"
            }
        },

        {
            "Mutton Korma",
            {"mutton","onion","yogurt","ginger","garlic","oil","salt","korma masala"},
            {
                "Fry onions until golden brown",
                "Add ginger garlic paste and mutton and cook for 15 minutes",
                "Add yogurt and korma masala and mix well",
                "Cover and cook on low heat for 60 minutes",
                "Serve hot with naan"
            }
        },

        {
            "Chicken Sajji",
            {"whole chicken","salt","spices","oil"},
            {
                "Marinate chicken with salt and spices for 120 minutes",
                "Preheat oven or charcoal grill",
                "Roast chicken for 90 minutes until fully cooked",
                "Brush oil during roasting",
                "Serve hot"
            }
        },

        {
            "Daal Makhni",
            {"black lentils","butter","cream","tomatoes","garlic","salt","spices"},
            {
                "Soak lentils overnight and boil until soft",
                "Heat butter and sauté garlic for 1 minute",
                "Add tomatoes and spices and cook for 10 minutes",
                "Add lentils and simmer for 40 minutes",
                "Finish with cream and serve hot"
            }
        },

        {
            "Chicken White Karahi",
            {"chicken","yogurt","cream","ginger","garlic","green chillies","oil","salt"},
            {
                "Heat oil and sauté ginger garlic paste",
                "Add chicken and cook for 10 minutes",
                "Add yogurt and green chillies and mix",
                "Cook on low heat for 15 minutes",
                "Finish with cream and serve hot"
            }
        },

        {
            "Beef Karahi",
            {"beef","tomatoes","ginger","garlic","green chillies","oil","salt","spices"},
            {
                "Heat oil and add ginger garlic paste",
                "Add beef and cook for 20 minutes",
                "Add tomatoes and spices and cook for 25 minutes",
                "Add green chillies and cook for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Aloo Palak",
            {"potatoes","spinach","onion","garlic","oil","salt","spices"},
            {
                "Boil spinach and blend into puree",
                "Heat oil and fry onions and garlic",
                "Add potatoes and cook for 10 minutes",
                "Add spinach puree and spices and cook for 15 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Fried Rice",
            {"chicken","rice","soy sauce","garlic","oil","salt","pepper"},
            {
                "Cook rice and set aside",
                "Heat oil and sauté garlic for 30 seconds",
                "Add chicken and cook for 8 minutes",
                "Add rice and soy sauce and stir fry for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Masoor Daal",
            {"red lentils","onion","garlic","oil","salt","spices"},
            {
                "Boil lentils with salt until soft",
                "Heat oil and fry garlic and onions",
                "Add spices and mix well",
                "Combine tarka with lentils and simmer for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Corn Soup",
            {"chicken","corn","egg","cornflour","salt","pepper","water"},
            {
                "Boil chicken in water and shred",
                "Add corn and chicken stock and bring to boil",
                "Add cornflour slurry and stir continuously",
                "Slowly add beaten egg while stirring",
                "Serve hot"
            }
        },

        {
            "Mutton Pulao",
            {"mutton","rice","onion","oil","salt","whole spices"},
            {
                "Heat oil and fry onions until golden",
                "Add mutton and cook for 20 minutes",
                "Add water and whole spices and cook until mutton is tender",
                "Add rice and cook until water dries",
                "Steam for 15 minutes and serve"
            }
        },
        
        {
            "Chicken Teriyaki",
            {"chicken","soy sauce","honey","garlic","ginger","oil","salt"},
            {
                "Mix soy sauce, honey, garlic, and ginger to prepare sauce",
                "Heat oil in a pan and cook chicken for 10 minutes until golden",
                "Add prepared sauce and simmer for 8 minutes",
                "Cook until sauce thickens and coats chicken",
                "Serve hot with rice"
            }
        },

        {
            "Japanese Chicken Katsu",
            {"chicken","breadcrumbs","egg","flour","oil","salt"},
            {
                "Flatten chicken breasts evenly",
                "Coat chicken with flour, egg, and breadcrumbs",
                "Heat oil and deep fry for 6 minutes per side",
                "Drain excess oil and rest for 2 minutes",
                "Serve sliced with sauce"
            }
        },

        {
            "Halal Chicken Ramen",
            {"chicken","noodles","garlic","ginger","soy sauce","oil","salt","water"},
            {
                "Boil chicken with garlic and ginger for 30 minutes",
                "Remove chicken and shred it",
                "Cook noodles in broth for 4 minutes",
                "Add soy sauce and shredded chicken",
                "Serve hot"
            }
        },

        {
            "English Roast Chicken",
            {"whole chicken","potatoes","garlic","butter","oil","salt","pepper"},
            {
                "Season chicken with salt, pepper, and garlic",
                "Roast in oven at 180 degrees for 75 minutes",
                "Turn potatoes halfway through cooking",
                "Rest chicken for 10 minutes before slicing",
                "Serve hot"
            }
        },

        {
            "Chicken Shepherd's Pie",
            {"chicken","potatoes","onion","carrot","butter","milk","salt"},
            {
                "Boil potatoes and mash with butter and milk",
                "Cook chicken with onions and carrots for 15 minutes",
                "Spread chicken mixture in baking dish",
                "Top with mashed potatoes",
                "Bake for 25 minutes until golden"
            }
        },

        {
            "Turkish Chicken Doner",
            {"chicken","yogurt","garlic","spices","oil","salt"},
            {
                "Marinate chicken with yogurt and spices for 2 hours",
                "Cook chicken on high heat for 15 minutes",
                "Slice thinly and pan fry for 5 minutes",
                "Rest for 3 minutes",
                "Serve in flatbread"
            }
        },

        {
            "Turkish Lentil Soup",
            {"red lentils","onion","carrot","garlic","oil","salt","water"},
            {
                "Wash lentils thoroughly",
                "Cook lentils with vegetables for 30 minutes",
                "Blend until smooth",
                "Simmer for another 10 minutes",
                "Serve hot"
            }
        },

        {
            "Mexican Chicken Tacos",
            {"chicken","tortilla","onion","capsicum","oil","salt","spices"},
            {
                "Cook chicken with spices for 12 minutes",
                "Sauté onion and capsicum for 5 minutes",
                "Warm tortillas on pan",
                "Fill tortillas with chicken mixture",
                "Serve hot"
            }
        },

        {
            "Mexican Chicken Quesadilla",
            {"chicken","tortilla","cheese","onion","oil","salt"},
            {
                "Cook chicken with salt and spices for 10 minutes",
                "Place tortilla on pan and add cheese and chicken",
                "Cover with another tortilla",
                "Cook each side for 3 minutes",
                "Serve sliced"
            }
        },

        {
            "Chicken Fajita",
            {"chicken","onion","capsicum","oil","salt","fajita spices"},
            {
                "Marinate chicken with fajita spices for 20 minutes",
                "Cook chicken on high heat for 10 minutes",
                "Add vegetables and cook for 5 minutes",
                "Stir continuously",
                "Serve hot"
            }
        },

        {
            "Mediterranean Grilled Chicken",
            {"chicken","olive oil","lemon","garlic","salt","herbs"},
            {
                "Marinate chicken with olive oil, lemon, and herbs for 60 minutes",
                "Grill chicken on medium heat for 15 minutes",
                "Turn occasionally",
                "Rest for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Pasta Alfredo",
            {"chicken","pasta","cream","butter","garlic","salt"},
            {
                "Cook pasta according to package instructions",
                "Cook chicken in butter for 8 minutes",
                "Add garlic and cream and simmer for 5 minutes",
                "Mix pasta into sauce",
                "Serve hot"
            }
        },

        {
            "Chicken Fried Rice",
            {"chicken","rice","egg","soy sauce","oil","salt"},
            {
                "Cook rice and let it cool",
                "Cook chicken in oil for 8 minutes",
                "Add egg and scramble",
                "Add rice and soy sauce and stir fry for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Spring Rolls",
            {"chicken","cabbage","carrot","roll wrappers","oil","salt"},
            {
                "Cook chicken and vegetables for 10 minutes",
                "Cool filling completely",
                "Wrap filling in wrappers",
                "Deep fry until golden",
                "Serve hot"
            }
        },

        {
            "Chicken Soup",
            {"chicken","carrot","potato","garlic","salt","water"},
            {
                "Boil chicken with water for 40 minutes",
                "Add vegetables and cook for 15 minutes",
                "Season with salt",
                "Simmer for 5 minutes",
                "Serve hot"
            }
        },

        {
            "Grilled Chicken Sandwich",
            {"chicken","bread","butter","lettuce","salt"},
            {
                "Grill chicken for 12 minutes",
                "Toast bread with butter",
                "Assemble sandwich with chicken and lettuce",
                "Cut and serve warm"
            }
        },

        {
            "Chicken Burger",
            {"chicken patty","bun","lettuce","cheese","oil","salt"},
            {
                "Cook chicken patty for 6 minutes per side",
                "Toast buns lightly",
                "Assemble burger with toppings",
                "Serve hot"
            }
        },

        {
            "Chicken Nuggets",
            {"chicken","breadcrumbs","egg","oil","salt"},
            {
                "Coat chicken pieces with egg and breadcrumbs",
                "Heat oil for frying",
                "Deep fry nuggets for 5 minutes",
                "Drain excess oil",
                "Serve hot"
            }
        },

        {
            "Chicken Caesar Salad",
            {"chicken","lettuce","cheese","olive oil","salt"},
            {
                "Grill chicken and slice thinly",
                "Wash and dry lettuce",
                "Mix lettuce with olive oil and salt",
                "Top with chicken and cheese",
                "Serve chilled"
            }
        },

        {
            "Baked Chicken Wings",
            {"chicken wings","oil","salt","spices"},
            {
                "Marinate wings with spices for 30 minutes",
                "Bake at 200 degrees for 35 minutes",
                "Turn halfway through cooking",
                "Serve hot"
            }
        },

        {
            "Chicken Satay",
            {"chicken","peanut butter","soy sauce","oil","salt"},
            {
                "Marinate chicken with sauce for 60 minutes",
                "Skewer chicken pieces",
                "Grill for 10 minutes",
                "Serve hot with sauce"
            }
        },

        {
            "Chicken Curry Thai Style (Halal)",
            {"chicken","coconut milk","garlic","ginger","oil","salt"},
            {
                "Heat oil and sauté garlic and ginger for 1 minute",
                "Add chicken and cook for 10 minutes",
                "Add coconut milk and simmer for 15 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Stuffed Peppers",
            {"chicken","bell peppers","onion","oil","salt"},
            {
                "Cook chicken and onion for 10 minutes",
                "Stuff mixture into peppers",
                "Bake at 180 degrees for 30 minutes",
                "Serve hot"
            }
        },

        {
            "Chicken Wrap",
            {"chicken","tortilla","lettuce","sauce","salt"},
            {
                "Cook chicken for 10 minutes",
                "Warm tortilla lightly",
                "Assemble wrap with fillings",
                "Roll tightly and serve"
            }
        },

        {
            "Grilled Salmon with Herbs",
            {"salmon","lemon","olive oil","garlic","salt","black pepper","herbs"},
            {
                "Marinate salmon with olive oil, lemon juice, garlic, salt, and herbs for 20 minutes",
                "Heat grill pan on medium heat",
                "Place salmon skin-side down and cook for 5 minutes",
                "Flip gently and cook for another 4 minutes",
                "Rest for 2 minutes before serving"
            }
        },

        {
            "Lamb Shawarma Wrap",
            {"lamb","garlic","yogurt","lemon","flatbread","salt","spices"},
            {
                "Marinate lamb with yogurt, garlic, lemon, salt, and spices for 2 hours",
                "Cook lamb on medium heat for 25 minutes until tender",
                "Slice meat thinly",
                "Warm flatbread lightly",
                "Wrap lamb and serve hot"
            }
        },

        {
            "Shrimp Garlic Butter",
            {"shrimp","butter","garlic","lemon","salt","black pepper"},
            {
                "Clean and pat dry shrimp",
                "Melt butter in pan over medium heat",
                "Add garlic and cook for 30 seconds",
                "Add shrimp and cook for 4 minutes until pink",
                "Finish with lemon juice and serve"
            }
        },

        {
            "Vegetable Sushi Rolls",
            {"sushi rice","nori","cucumber","carrot","avocado","vinegar","salt"},
            {
                "Cook sushi rice and season with vinegar and salt",
                "Place nori sheet on mat",
                "Spread rice evenly and add vegetables",
                "Roll tightly using mat",
                "Slice and serve"
            }
        },

        {
            "Mushroom Risotto",
            {"rice","mushrooms","onion","butter","vegetable stock","salt"},
            {
                "Sauté onions in butter for 5 minutes",
                "Add mushrooms and cook until soft",
                "Add rice and stir for 2 minutes",
                "Add stock gradually while stirring for 20 minutes",
                "Serve creamy and hot"
            }
        },

        {
            "Lamb Chops with Rosemary",
            {"lamb chops","olive oil","garlic","rosemary","salt","pepper"},
            {
                "Marinate lamb chops with oil, garlic, rosemary, salt, and pepper for 30 minutes",
                "Heat grill pan on medium-high heat",
                "Grill chops for 4 minutes per side",
                "Rest for 5 minutes",
                "Serve warm"
            }
        },

        {
            "Fish Stew",
            {"fish","onion","tomatoes","garlic","olive oil","salt","herbs"},
            {
                "Heat oil and sauté onions for 5 minutes",
                "Add garlic and tomatoes and cook until soft",
                "Add fish pieces gently",
                "Simmer on low heat for 12 minutes",
                "Serve hot"
            }
        },

        {
            "Falafel Wrap",
            {"chickpeas","onion","garlic","coriander","flour","oil","salt"},
            {
                "Blend chickpeas with onion, garlic, and spices",
                "Shape into small balls",
                "Deep fry until golden for 4 minutes",
                "Drain excess oil",
                "Wrap in flatbread and serve"
            }
        },

        {
            "Prawn Fried Rice",
            {"rice","prawns","garlic","onion","soy sauce","oil","salt"},
            {
                "Cook rice and allow it to cool",
                "Stir fry prawns for 3 minutes and remove",
                "Cook onion and garlic for 2 minutes",
                "Add rice and soy sauce",
                "Return prawns and mix well"
            }
        },

        {
            "Spinach and Cheese Pasta",
            {"pasta","spinach","cheese","garlic","olive oil","salt"},
            {
                "Boil pasta until al dente",
                "Sauté garlic in olive oil for 1 minute",
                "Add spinach and cook until wilted",
                "Add pasta and cheese",
                "Mix well and serve hot"
            }
        },

        {
            "Grilled Halloumi",
            {"halloumi cheese","olive oil","lemon","black pepper"},
            {
                "Slice halloumi evenly",
                "Brush with olive oil",
                "Grill for 2 minutes per side",
                "Drizzle lemon juice",
                "Serve immediately"
            }
        },

        {
            "Seafood Paella",
            {"rice","shrimp","fish","tomatoes","olive oil","salt","paprika"},
            {
                "Sauté tomatoes in olive oil for 5 minutes",
                "Add rice and stir well",
                "Add water and simmer for 20 minutes",
                "Add seafood and cook for 10 minutes",
                "Rest for 5 minutes before serving"
            }
        },

        {
            "Vegetable Quesadilla",
            {"tortilla","bell peppers","onion","cheese","oil","salt"},
            {
                "Cook vegetables in oil for 5 minutes",
                "Place vegetables and cheese in tortilla",
                "Cook on pan until cheese melts",
                "Flip and cook other side",
                "Cut and serve hot"
            }
        },

        {
            "Lentil Patties",
            {"lentils","onion","garlic","breadcrumbs","salt","oil"},
            {
                "Boil lentils until soft and mash",
                "Mix with onion, garlic, and breadcrumbs",
                "Shape into patties",
                "Pan fry for 4 minutes per side",
                "Serve hot"
            }
        },

        {
            "Grilled Vegetable Skewers",
            {"zucchini","bell pepper","mushrooms","olive oil","salt"},
            {
                "Cut vegetables into equal pieces",
                "Thread onto skewers",
                "Brush with oil and salt",
                "Grill for 8 minutes turning sides",
                "Serve warm"
            }
        },

        {
            "Shrimp Tempura",
            {"shrimp","flour","cornflour","cold water","oil","salt"},
            {
                "Prepare light batter with cold water",
                "Dip shrimp into batter",
                "Deep fry for 3 minutes",
                "Drain excess oil",
                "Serve crispy"
            }
        },

        {
            "Pumpkin Soup",
            {"pumpkin","onion","garlic","cream","salt","water"},
            {
                "Boil pumpkin until soft",
                "Sauté onion and garlic for 5 minutes",
                "Blend pumpkin with water",
                "Add cream and simmer for 10 minutes",
                "Serve warm"
            }
        },

        {
            "Stuffed Bell Peppers",
            {"bell peppers","rice","tomatoes","onion","olive oil","salt"},
            {
                "Cook rice halfway",
                "Mix rice with onion and tomatoes",
                "Stuff mixture into peppers",
                "Bake for 35 minutes",
                "Serve hot"
            }
        },

        {
            "Baked Fish with Lemon",
            {"fish fillet","lemon","olive oil","garlic","salt"},
            {
                "Preheat oven to medium heat",
                "Season fish with lemon, oil, and garlic",
                "Bake for 18 minutes",
                "Rest for 3 minutes",
                "Serve warm"
            }
        },

        {
            "Vegetable Noodle Stir Fry",
            {"noodles","carrot","cabbage","garlic","soy sauce","oil"},
            {
                "Boil noodles and drain",
                "Stir fry vegetables for 5 minutes",
                "Add noodles and soy sauce",
                "Mix on high heat for 3 minutes",
                "Serve hot"
            }
        },

        {
            "Cheese Omelette",
            {"eggs","cheese","butter","salt","pepper"},
            {
                "Beat eggs with salt and pepper",
                "Melt butter in pan",
                "Pour eggs and cook gently",
                "Add cheese and fold omelette",
                "Serve immediately"
            }
        },

        {
            "Lamb Stuffed Flatbread",
            {"lamb mince","onion","flatbread","salt","spices","oil"},
            {
                "Cook lamb mince with onion and spices for 15 minutes",
                "Fill flatbread with cooked lamb",
                "Toast on pan until crisp",
                "Flip and cook evenly",
                "Serve hot"
            }
        },

        {
            "Chickpea Salad",
            {"chickpeas","cucumber","tomatoes","lemon","olive oil","salt"},
            {
                "Rinse cooked chickpeas",
                "Chop vegetables finely",
                "Mix everything with lemon and oil",
                "Season with salt",
                "Serve fresh"
            }
        },

        {
            "Baked Zucchini Fries",
            {"zucchini","breadcrumbs","cheese","oil","salt"},
            {
                "Cut zucchini into sticks",
                "Coat with breadcrumbs and cheese",
                "Bake for 25 minutes",
                "Turn halfway",
                "Serve crispy"
            }
        }




    };

    for (const auto& recipe : recipes) {

        string filename = recipe.name + ".txt";

        if (fs::exists(filename)) {
            continue; // do not overwrite existing recipes
        }

        ofstream F(filename);

        F << "Name: " << recipe.name << "\n\n";
        F << "Ingredients: ";

        for (size_t i = 0; i < recipe.ingredients.size(); i++) {
            F << recipe.ingredients[i];
            if (i != recipe.ingredients.size() - 1)
                F << ",";
        }

        for (size_t i = 0; i < recipe.steps.size(); i++) {
            F << "\n\nStep " << i + 1 << ": " << recipe.steps[i];
        }

        F.close();
    }
}


void clearscreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void suggestRecipe(){

A_M_R AMR;

// taking input from the user for suggesting recipes   
    vector<string> UserIngredients;
    string line;

    cout << "\nEnter the ingredients you have (comma separated) : ";
    getline(cin,line);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    istringstream stream(line);

    string ingredient;

    while ( getline(stream , ingredient , ',') ){
   
        if (ingredient[0] == ','){
            ingredient.erase(0,1);
        } 
       
        if (ingredient[ingredient.size()-1] == ','){
            ingredient.erase(ingredient.size()-1);
        } 
        
        UserIngredients.push_back(ingredient);
    }

    // matching the ingredients
    int match=0;
    int total=0;
    int percent=0;

    vector<string> C_ingredients;
    set<string> ing;

    for(int i=0; i<Rec.Recipe.size(); i++){

        // match=0;
        // total = Rec.Recipe[i].ingredients.size();

        for(int j=0; j<UserIngredients.size(); j++){
            match=0;
        total = Rec.Recipe[i].ingredients.size();
            for(int k=0; k<Rec.Recipe[i].ingredients.size(); k++){

                if (UserIngredients[j].size() < Rec.Recipe[i].ingredients[k].size()){
                    string each;
                    istringstream str(Rec.Recipe[i].ingredients[k]);
                    
                    while(str >> each){
                        if (UserIngredients[j] == each){
                                ing.insert(each);
                                match++;
                        }
                        
                    }
                }

                else if (manipulate(UserIngredients[j])==manipulate(Rec.Recipe[i].ingredients[k])){
                    ing.insert(UserIngredients[j]);
                    match++;
                }
            }

        }
       
        // storing percent and name in the structure Ratched Recipe
        
        
        MatchedRecipe mr;
        mr.Mname = Rec.Recipe[i].name;
        

        // cout << "For " << Rec.Recipe[i].name <<" match is " << match << " total is " << total  << " percentage is " << percent << endl;
        
        AMR.M_Rec.push_back(mr) ;
        
        AMR.M_Rec[i].matched_per = percent;

    }
     
    // for (int l=0; l<AMR.M_Rec.size(); l++){
    //     cout << "Name : " << AMR.M_Rec[l].Mname << endl;
    //     cout << "Percentage : " << AMR.M_Rec[l].matched_per << endl;
    // }
    
// asking user if he wants to list all recipes with percentage or listing recipes by entering percentage 
    int ch;
    cout << "Press 1. to List all Recipes suggesstions \nPress 2. to List recipes by giving minimum matching percentage \nEnter your choice: ";
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (ch==1){
        // listt all
        clearscreen();
        for (int i=0; i<AMR.M_Rec.size(); i++){
            cout << "\nRecipe name : " << AMR.M_Rec[i].Mname <<endl ;
            cout << "\nMatched Percentage : " << AMR.M_Rec[i].matched_per << endl << endl ;
        }
    }
    else if (ch==2){
        //list specific
        clearscreen();
    
        long int Up;

        while (true){
            
            cout << "Enter minimum percentage : ";
            cin >> Up;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (Up > 100 || Up <0){
                Up=110;
            }
            if (Up<100 && Up>0){
                break;
            }
            else{
                cout << "Enter valid percentage\n";
            }
        }
       
        clearscreen();
        for (int i=0; i<AMR.M_Rec.size(); i++){
            if ( AMR.M_Rec[i].matched_per > 100){
                AMR.M_Rec[i].matched_per = 100;
            }
            if ( AMR.M_Rec[i].matched_per >= Up ){
                cout << "\nRecipe name : " << AMR.M_Rec[i].Mname <<endl ;
                cout << "\nMatched Percentage : " << AMR.M_Rec[i].matched_per << endl << endl ;
            }
            if (i==AMR.M_Rec.size()-1 && AMR.M_Rec[i].Mname.empty()){
                cout << "No recipe found\n";
                cin.get();
                break;
            }
    
        }

    }
    else{
        cout << "\nEnter valid number\n";
        
    }
    cin.get();
    
}

void starttimer(int totalseconds){
    while (totalseconds > 0){
        int m = totalseconds/60;
        int s = totalseconds%60;
        cout << "\r⏱️ " << m << "m " << s << "s " << "remaining" << flush;
        this_thread::sleep_for(chrono::seconds(1));
        totalseconds--;
    }
    cout << "\n✅ Time completed!\n";
}

int durationCal(const string &s){
    string str;
    istringstream ss(s);
    while(ss >> str){
        
        if (isdigit(str[0])){
            
            int n = stoi(str);

            ss >> str;
            if (str == "s" || str == "sec" || str == "second" || str == "seconds"){
                return 0;
            }
            return n*60;
        }
    }
    return 0;
}

void cook(){
    int n;
    cout << "Welcome to COOKING MODE\n\n";

    // printing all recipes
    ListAll();
    cout << "\nEnter the recipe number to start cooking: ";
    cin >> n; 
    cin.ignore();
    clearscreen();
    for(int i=0; i<Rec.Recipe[n-1].steps.size(); i++){
// if first  iteration then first show ingredients first
        if (i==0){
            cout << "First gather the ingredients\n\n";
            for(int j=0; j<Rec.Recipe[n-1].ingredients.size(); j++){

                cout << Rec.Recipe[n-1].ingredients[j] ;

                if(j!=Rec.Recipe[n-1].ingredients.size()-1) cout << ", ";
                
            }
            
            cout << "\n\nPress ENTER when you have gathered all the ingredients...\n";
            cin.get();
        }
// couting steps
        cout << "Step " << i+1 << ": " << Rec.Recipe[n-1].steps[i] << endl;
        
        if (durationCal(Rec.Recipe[n-1].steps[i]) != 0) {
            char c;
            cout << "\nDo you want to start a timer (y/n)? ";
            cout.flush();   // force output
            cin >> c;
            cout << endl;

            // CLEAR buffer properly
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (c == 'y' || c == 'Y') {
                starttimer(durationCal(Rec.Recipe[n-1].steps[i]));
            }
            
        }  
        else{
                cin.get();
            }

    }
    cout << "Cngratulations! you have completed all the steps\n";
    cin.get();
}

void generateShoppinglist(){
    ListAll();
    int n;
    cout << "Enter the Recipe number to generate Shopping List for: ";
    cin >> n;
    cin.ignore();

    clearscreen();
    string recipe = Rec.Recipe[n-1].name;
    cout << "\n\nHere is your shopping list for " << recipe << ":\n\n";
    for(int i=0; i<Rec.Recipe[n-1].ingredients.size(); i++){
        cout  << i+1 << ". " << Rec.Recipe[n-1].ingredients[i] << endl; 
    }
    cout << "\nPress any key to continue "; 
    cin.get();
}

void Edit(){
    RecipeStructure R;
    
    string P_file_N;
    int n;
    string line;
    ListAll();

    cout << "Enter recipe number to edit: ";
    cin >> n;
    clearscreen();
    int i=1;
    for (const auto check : fs::directory_iterator(".")){
        if (check.path().extension()==".txt"){
            if(i==n){
                string F_name = check.path().filename();
                int change;
                clearscreen();

                cout << "\nPress 1 to change name\nPress 2 to change Ingredients\nPress 3 to change Steps\n\nEnter your Choice: ";
                cin >> change;
                
                ifstream R_file(F_name);
                //reading name
                    getline(R_file , R.name);
                    R.name = R.name.substr(6, R.name.size()-5);
                    //cout << "R.name is : " << R.name;
                    P_file_N=R.name;
                    //reading ingreadients
                        getline(R_file, line);
                        getline(R_file, line);
                        line=line.substr(13,line.size());
                        stringstream ss(line);
                        string word;
                        while (getline(ss,word,',')){
                            //cout << "\n(in reading ingredients) Word is : " << word << endl; 
                            R.ingredients.push_back(word);
                        }

                        // for(string s: R.ingredients){
                        //     cout << "The ingredient is : " << s << endl; 
                        // }

                        // reading steps
                            R.steps.clear();
                            int j=1;
                            while(getline(R_file, line)){
                                if(line.empty()){
                                    getline(R_file, line);
                                }
                                
                                string nl;
                                //cout << "\nThe line number " << j << " read from " << F_name << " is : " << line <<endl ;

                                if(j>=10){
                                    line=line.substr(9,line.size());
                                }
                                if(j<10){
                                    line=line.substr(8,line.size());
                                }
                                
                                nl=line;
                                //cout << "\nThe same line after substring is : " << line << endl;
                                //cout << "The line pushing back in R.step: " << nl << endl;
                                R.steps.push_back(nl);
                                //cout << "\nIn reading steps, R.step " << j << " is : " << R.steps[j] << endl;
                                j++;
                            }

                            // for(string s: R.steps){
                            //     cout << "The line is : " << s << endl; 
                            // }


                switch (change){

                    case 1: {
                            // getline(R_file , R.name);
                            // R.name = R.name.substr(7, R.name.size()-5);
                            cout << "Enter new name: ";
                            cin >> R.name;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        break;

                    case 2: {
                            //getline(R_file, line);
                            // getline(R_file, line);
                            // line=line.substr(13,line.size());
                            // stringstream ss(line);
                            // string word;
                            // while (getline(ss,word,',')){
                            //     R.ingredients.push_back(word);
                            // }
                            do{
                                int i=1;
                                for(string indv_ingredients : R.ingredients){
                                    cout << i << ". " << indv_ingredients << endl;
                                    i++;
                                }

                                cout << "\nEnter ingredient number to change: ";
                                cin >> change;
                                cin.ignore();
                                cout << "\nEnter new ingredient: ";
                                getline(cin, line);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                R.ingredients[change-1] = line;

                                char c;
                                cout << "Do u want to replace any other ingredient (y/n): ";
                                cin >> c;
                                cout << endl;
                                if (c == 'n' || c== 'N') break;
                                
                            } while(true);
                        }
                        break; 

                    case 3:{
                            do{
                                getline(R_file, line);
                                getline(R_file, line);
                                
                                
                                int k=1;
                                cout << endl;
                                for(string showSteps : R.steps){
                                    cout << "Step " << k << " is: " << showSteps << endl;
                                    k++;
                                }
                                cout << "\nEnter line number to change: ";
                                cin >> n;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                cout << "Enter new line: ";
                                getline (cin ,line);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                // replacing logic left
                                R.steps[n-1]=line;

                                char c;
                                cout << "\nDo u want to replace any other step (y/n): ";
                                cin >> c;
                                if (c == 'n' || c== 'N') break;

                            } while (true);

                            
                        }
                        break;

                    default:
                        cout << "\nThe key you pressed is not a valid number\n";
                        break;

                }
                R_file.close();

                // deleting previous and creating new file with changes

                fs::remove(P_file_N+".txt");

                int i=1;
                ofstream N_file(R.name+".txt");
                N_file << "Name: " << R.name << endl << endl;
                N_file << "Ingredients: ";
                for(string s : R.ingredients){
                    N_file << s ;
                    if (i!=R.ingredients.size()){
                        N_file << ",";

                    }
                    else{
                        N_file << endl << endl;
                        i=1;
                        break;
                    }
                    i++;
                }
                
                for(string s : R.steps){
                    N_file << "Step " << i << ": " << s ;
                    
                    // cout << "i is: " << i << endl;
                    // cout << "R.step.size() is: " << R.steps.size() << endl;
                    //cin.get();
                    if(i!=R.steps.size()){
                        
                        N_file << endl << endl;

                    }
                    i++;
                }
                cout << "Changes saved successfully!";
                N_file.close();

                break;
            }
            i++;
        }
    }
    cin.get();
}

// string manipulate (string str){
//     for (char &x : str ){
//         x = tolower(x);
//     }
//     str.erase( remove_if( str.begin() , str.end(), ::isspace), str.end() ) ;
//     return str;
// }

void Search(){
    string UserInput;
    cout << "Enter the Recipe to search: ";
    getline(cin,UserInput);

    
    manipulate(UserInput);
    
    string name;
    bool found=true;
    for (const auto list : fs::directory_iterator(".")){
        if(list.path().extension()==".txt"){
            name = list.path().filename().replace_extension();
            manipulate(name);
            if (UserInput == name){
                found = true;
                cout << "You have this recipe saved.\n";
                break;
            }
            else {
                found = false;
            }
        }
    }

    if (found == false){
        cout << "Could not find recipe\n";
    }

    cin.get();
    clearscreen();

}

void ListAll(){
    
    int i=1;
    string name;
    cout << endl << "Here are your saved recipes:- \n";
    for (const auto list : fs::directory_iterator(".")){
        if(list.path().extension()==".txt"){
            name = list.path().filename().replace_extension();
            cout << i << ". " << name << endl;
            i++;
        }
    }
    cout << endl;
    cout << "\nPress any key to continue...\n";
    cin.get();
    
}

void delRecipe(){
    
    ListAll();
    
    string file, name;
    int n;
    cout << "Enter the recipe number or name to delete : ";
    getline(cin , name);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
// check if user enterd a the name or an integer
    istringstream ss(name);
    // ss>>n;
    // cout << "1st condition: " << n;
    // cout << "2nd condition: " << ss.eof();
    // cin.get();
    int l=0;
    if(isdigit(name[l]) ){
        n = stoi(name);
        
        
        if (n<1 || n>Rec.Recipe.size()) {cout << "Enter correct recipe name or number\n"; cin.get(); return;}

        char c;
        cout << "Are you sure you want to delete " << Rec.Recipe[n-1].name << " (y/n) \n";
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(c=='y'||c=='Y'){
            fs::remove(Rec.Recipe[n-1].name+".txt");
        }
        
    }
    else{
        if (fs::exists(name + ".txt")){
            fs::remove(name + ".txt");
            cout << "Recipe deleted successfully ! \n";
            cin.get();
        }
        else {
            cout << "Enter correct recipe name or number\n";
        }
    }
    clearscreen();
}

void addRecipe(){

    RecipeStructure r;
    string ingredients;
    cout << "Enter the name of your Recipe: ";
    getline(cin, r.name);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream file( r.name + ".txt" );
    if(!file){
        cerr << "Error adding recipe name!";
    }
    
    cout << "Enter Ingredients ( Separate each one with ',' ) : ";
    getline(cin, ingredients);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file << "Name: " << r.name << endl << endl;
    
    stringstream ss(ingredients);
    string word;
    while (getline(ss,word,',')){
        r.ingredients.push_back(word);
    }
    file << "Ingredients: " ;
    int i=0;
    for (string x : r.ingredients){
        file << x ;
        if(i!=r.ingredients.size()-1) file << ",";
        i++;
    }
    file << endl;
    
    string line;
    cout << "Now Enter the steps (type \"done\" when completed)\n\n";

    for (int i=1; ; i++){
        cout << "Enter step " << i << " : ";
        getline(cin,line);
        if ( line == "done" ) break;
        file << "\nStep " << i << ": " << line << endl ;

    }
    file.close();
    cout << "\nRecipe Saved Successfully!\n";
    cin.get();
    clearscreen();
}

void menu(){
    cout << "\n\n========== Welcome to Recipe Manager ==========";
    cout << "\nPress 1. to add a recipe\n";
    cout << "Press 2. to delete a recipe\n";
    cout << "Press 3. to view all recipes\n";
    cout << "Press 4. to search a recipe\n";
    cout << "Press 5. to edit a recipe\n";
    cout << "press 6. to generate shopping list\n";
    cout << "Press 7. for cooking mode\n";
    cout << "Press 8. for recipe suggestions\n";
    cout << "Press 9. to exit\n";
    cout << "===============================================";
    cout << "\nEnter your choice: ";
}

int main(){
    int n;
    CreateBuiltInRecipes();
    LoadRecipes();
    
    while(true){
        
        loadRecipeName();
        clearscreen();
        menu();
        
        cin >> n;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter valid number : ";
            cin >> n;
            cout << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if(n==9){
            cout << "\nGoodbye!\n        Thanks for using me\n\n";
            break;
        }
        switch(n){
            case 1:
                clearscreen();
                addRecipe();
                break;
            case 2:
                clearscreen();
                delRecipe();
                break;
            case 3:
                clearscreen();
                ListAll();
                break;
            case 4:
                clearscreen();
                Search();
                break;
            case 5:
                clearscreen();
                Edit();
                break;
            case 6:
                
                generateShoppinglist();
                break;
            case 7:
                clearscreen();
                cook();
                break;
            case 8:
                clearscreen();
                suggestRecipe();
                break;
            default : 
                cout << "Enter valid number\n";
        }
    }
    
    return 0;
}
