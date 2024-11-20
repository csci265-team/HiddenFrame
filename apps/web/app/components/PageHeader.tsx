import { LoaderFunction } from "@remix-run/node";
import { getSession } from "../session";
import { useLoaderData } from "@remix-run/react";

export const loader: LoaderFunction = async ({ request }) => {
    const session = await getSession(request.headers.get("Cookie"));
    const username = session.get("username");

    return { username };
};

export const PageHeader = () => {
    const data = useLoaderData<typeof loader>();
    let username = '';
    if (data) username = data.username;

    return (
        <header className="flex flex-col items-center gap-9">
            <a href="/"><h1 className="text-4xl font-[Outfit] font-black">HiddenFrame</h1></a>
            {username && <a href="/user"> <h2 className="text-2xl font-black">Logged In as {username}</h2></a>}
        </header>
    );
}

