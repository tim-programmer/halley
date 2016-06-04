local function update(time, families)
    local a = 0
    local elems = families["mainFamily"].elems
    for j = 1, #elems do
        a = a + 1
    end
    Halley.print("Updated " .. a .. " elements.")
end

function makeUpdate(systemPtr, numFamilies)
    local families = {}
    local familiesList = {}
    
    for i = 1, numFamilies do
        local name = Halley.getFamilyName(systemPtr, i - 1)
        local fam = {}
        fam.idx = i
        fam.name = name

        families[name] = fam
        familiesList[i] = fam
    end
    
    return function(time)
        for i = 1, numFamilies do
            Halley.print("Time is " .. time .. ", family is " .. i)
            local elems = {}
            local n = Halley.getFamilyCount(systemPtr, i - 1)
            
            for j = 1, n do
                elems[j] = {}
                Halley.getFamilyEntry(systemPtr, i - 1, j - 1, elems[j])
            end
            familiesList[i].elems = elems
        end
        
        update(time, families)
    end
end
